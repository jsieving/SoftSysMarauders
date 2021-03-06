// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include "mac_mapping.h"

#define PORT 8080
#define BUF_SIZE 1024

int username_flag = 0; // 0: username not set
int sock = 0; // used by sending (parent) thread

void * receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[BUF_SIZE];
 sockfd = (int) socket;
 for (;;) {
  memset(buffer, 0, BUF_SIZE);
  ret = recv(sockfd , buffer, BUF_SIZE,0);
  if(ret == 0){ //ret = 0
    printf("Server not available! Please Ctrl-D");
    pthread_exit(NULL);
    exit(0);
  }
  else if (ret < 0) {
   printf("Error receiving data!\n");
  } else {
   fputs(buffer, stdout);
   
    char words[4][32];
    int word_ind = 0;
    int char_ind = 0;
    int buf_counter = 0;

    while (buffer[buf_counter] != '\0') {
      if (buffer[buf_counter] == ',') {
        words[word_ind][char_ind] = '\0';
        word_ind++;
        char_ind = 0;
      } else {
        words[word_ind][char_ind] = buffer[buf_counter];
        char_ind++;
      }
      buf_counter++;
    }
    // printf("%s -- %s -- %s -- %s\n", words[0], words[1], words[2], words[3]);

    //iterates through linked list to find user to update
    Entity* curr = (Entity*) app.head;
    Entity *next;
    Entity* found_usr;
    int found_flag = 0;

    // make sure the first node isn't the match
    if(strcmp(curr->name, name) == 0){
			found_usr = curr;
      found_flag = 1;
    }
    while(curr->next != NULL){
			next = curr->next;
      if(strcmp(next->name, name) == 0){
        found_usr = next;
        found_flag = 1;
      }
      curr = curr->next;
    }

    //adds new users or modifies location of the existing user
    if(found_flag == 0) {
      Entity* initPlayer(atoi(words[1]), atoi(words[2]), words[0], atoi(words[3]));
    } else {
      found_usr->x = atoi(words[1]);
      found_usr->y = atoi(words[2]);
      found_usr->floor = atoi(words[3]);
      printf("%s -- %d -- %d -- %d\n", words[0], found_usr->x, found_usr->y, found_usr->floor);
    }
  }
 }
}

/* Set up the signal catcher.
*/
int catch_signal(int sig, void (*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

/* Signal handler for SHUTDOWN
*/
void handle_shutdown(int sig) {
    if (sock)
        close(sock);
    fprintf(stderr, "\nYour connection has been terminated.\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in serv_addr;
    char username[BUF_SIZE];
    char buffer[BUF_SIZE] = {0};
    char * serverAddr;
    pthread_t rThread;


    if (catch_signal(SIGINT, handle_shutdown) == -1) {
        error("Signal catcher setup failed. Setting interrupt handler"); }

    if (argc > 1) { //checks that user input server ip address
      serverAddr = argv[1]; //to get server ip address from command line
    } else {
      serverAddr = "127.0.0.1";
      printf("Server ip address not specified. Set to %s.\n", serverAddr);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serverAddr);
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //creating a new thread for receiving messages from the server
    int ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sock);
    if (ret) {
     printf("ERROR: Return Code from pthread_create() is %d\n", ret);
     exit(1);
    }

    char message_buffer[BUF_SIZE] = {0};

    if(!username_flag){
      printf("Marauders' Map v1.0\n");
      fgets(buffer, BUF_SIZE, stdin);
      int length = strlen(buffer);
      strncpy(username, buffer, length-1);
      username[length+1] = '\0';
      sprintf(message_buffer,"New user joined: %s\n", username);
      ret = send(sock, message_buffer, BUF_SIZE, 0);
      if(ret < 0) {
        printf("Error sending data");
        exit(1);
      }
      username_flag = 1;
    }

    char* filename = "MAC_rooms.txt";
    GHashTable* room_lookup = make_mapping(filename);
    Queue* loc_log = make_queue(20);

    while(1) {
        memset(message_buffer, 0, BUF_SIZE);
        Record* last_loc = location(room_lookup);
        enqueue(last_loc, loc_log);
        create_message(loc_log, message_buffer, BUF_SIZE);
        ret = send(sock, message_buffer, BUF_SIZE, 0);
        if(ret < 0) {
          printf("Error sending data");
          exit(1);
        }
        sleep(5);
    }
    return 0;
}
