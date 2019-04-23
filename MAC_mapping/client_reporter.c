#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> //close
#include <arpa/inet.h> // htons, inet_pton, includes netinet/in -> sys/socket
#include <string.h> // memset
#include <errno.h> // strerror
#include "mac_mapping.h" // create_message

#define PORT 8888
#define MAX_MSG 80

void send_message(int sock_fd) {
  char out_buffer[MAX_MSG+1];
  create_message(out_buffer, MAX_MSG+1);
  send(sock_fd, out_buffer, MAX_MSG * sizeof(char), 0);
  puts("Message sent\n");
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

  send_message(sock_fd);

  close(sock_fd);
  return 0;
}
