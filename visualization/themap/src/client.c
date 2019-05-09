// Client side C/C++ program to demonstrate Socket programming

#include "client.h"


int receiveMessage(void * socket) {
  puts("Hello from receiver!");

  // receiver process is forked from main
  int sockfd, ret;
  char recv_buffer[BUF_SIZE]; // holds the message received by client
  sockfd = (int) socket;
  for (;;) {
      memset(recv_buffer, 0, BUF_SIZE);
      ret = recv(sockfd , recv_buffer, BUF_SIZE,0);
      if(ret == 0){
        printf("Server not available! Please Ctrl-D");
        exit(0);
      }
      else if (ret < 0) {
        printf("Error receiving data!\n");
      } else {
        char* in_message = strdup(recv_buffer);
        char words[4][32];
        int word_ind = 0;
        int char_ind = 0;
        int buf_counter = 0;

        while (in_message[buf_counter] != '\0') {
          if (in_message[buf_counter] == ',') {
            words[word_ind][char_ind] = '\0';
            word_ind++;
            char_ind = 0;
          } else {
            words[word_ind][char_ind] = in_message[buf_counter];
            char_ind++;
          }
          buf_counter++;
        }
        printf("%s -- %s -- %s -- %s\n", words[0], words[1], words[2], words[3]);
      }
   }
   return 0;
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
    if (app.sock)
        close(app.sock);
    fprintf(stderr, "\nYour connection has been terminated.\n");
    exit(EXIT_SUCCESS);
}

// run_client
int run_client(void* socket)
{

    int csock = (int) socket;
    int username_flag = 0; // 0: username not set
    // sock = (int) socket;
    char un_buffer[BUF_SIZE] = {0}; // used to read in username
    char username[BUF_SIZE]; // used to store username
    char send_buffer[BUF_SIZE] = {0}; // used to store outgoing message

    if(!username_flag){
      printf("Marauders' Map v1.0\n");
      fgets(un_buffer, BUF_SIZE, stdin);
      int length = strlen(un_buffer);
      strncpy(username, un_buffer, length-1);
      username[length+1] = '\0';
      sprintf(send_buffer, "New user joined: %s\n", username);
      int ret = send(csock, send_buffer, BUF_SIZE, 0);
      if(ret < 0) {
        printf("Error sending data");
      }
      username_flag = 1;
      // tell the app to running
      app.start = 1;
    }

    char* filename = "graphics/MAC_rooms.txt";
    // key: mac address (char*)
    // value: Room *
    GHashTable* room_lookup = make_mapping(filename);
    Queue* loc_log = make_queue(20); // max size is 20
    Record* last_loc;

    while(1) {
        memset(send_buffer, 0, BUF_SIZE);
        last_loc = location(room_lookup);
        enqueue(last_loc, loc_log);
        initPlayer(last_loc->x, last_loc->y, username, last_loc->level);
        // The string of x, y, floor is stored in message_buffer
        create_message(username, loc_log, send_buffer, BUF_SIZE); // calculate average loc from queue and send it
        int ret = send(csock, send_buffer, BUF_SIZE, 0);
        if(ret < 0) {
          printf("Error sending data");
          exit(1);
        }
        // parse message and update list of user locations
        sleep(2);
    }
    return 0;
}
