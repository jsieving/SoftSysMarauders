#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> //close
#include <arpa/inet.h> // htons, inet_pton, includes netinet/in -> sys/socket
#include <string.h> // memset
#include <errno.h> // strerror
#include "mac_mapping.h" // get_near_rooms

#define PORT 8888
#define MAX_MSG 80

void comm_loop(int sock_fd) {
  int i = 0;
  int place;
  int valread = 0;
  int rooms;
  char out_buffer[MAX_MSG+1];
  char in_buffer[MAX_MSG+1];

  int max_rooms = 3;
  Room* near_rooms[max_rooms+1];
  near_rooms[max_rooms] = NULL;
  int strength_array[max_rooms];

  while(1) {
    rooms = get_near_rooms(near_rooms, strength_array, max_rooms);
    i = 0;
    place = 0;
    while (i < rooms && place < MAX_MSG) { // This is weak protection, since place increases quickly
      place += sprintf(&(out_buffer[place]), "%s:%d;", near_rooms[i]->room_num, strength_array[i]);
      i++;
    }
    i = 0;
    out_buffer[MAX_MSG] = '\0';
    send(sock_fd, out_buffer, MAX_MSG * sizeof(char), 0);
    memset(out_buffer, MAX_MSG * sizeof(char), ' ');
    puts("sent\n");

    while ((valread = recv(sock_fd, in_buffer, MAX_MSG * sizeof(char), 0)) != 0) {
      if (valread == -1) {
        error("Error in client while receiving");
      }
      in_buffer[valread] = '\0';
      printf("From Server : %s", in_buffer);
      memset(in_buffer, MAX_MSG * sizeof(char), ' ');
    }
  }
}

int main(int argc, char* argv[]) {
  int sock_fd;
  struct sockaddr_in serv_addr;
  char* serv_addr_str;

  if (argc > 1) {
    serv_addr_str = argv[1];
  } else {
    serv_addr_str = "127.0.0.1";
  }

  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("Socketread creation error");
	}

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, serv_addr_str, &serv_addr.sin_addr)<=0) {
    error("Invalid server IP address/address type not supported");
  }

  if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    error("Connection failed");
  }

  puts("Connected!\n");

  comm_loop(sock_fd);

  close(sock_fd);
  return 0;
}
