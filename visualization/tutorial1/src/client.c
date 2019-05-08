// Client side C/C++ program to demonstrate Socket programming

#include "client.h"

#define PORT 8080
#define BUF_SIZE 80

int sock = 0; // used by sending (parent) thread

void * receiveMessage(void * socket) {
  puts("Hello from receiver!");

  // receiver process is forked from main
  int sockfd, ret;
  char buffer[BUF_SIZE]; // holds the message received by client
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

// run_client
void* run_client(void* ip) // char* ip
{
    struct sockaddr_in serv_addr;
    char * serverAddr;
    pthread_t recvThread;

    if (catch_signal(SIGINT, handle_shutdown) == -1) {
        error("Signal catcher setup failed. Setting interrupt handler"); }

    if (ip != NULL) { //checks that user input server ip address
      serverAddr = (char*) ip; //to get server ip address from command line
    } else {
      serverAddr = "127.0.0.1";
      printf("Server ip address not specified. Set to %s.\n", serverAddr);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("Socket creation error");
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serverAddr);
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
    {
        error("Invalid address/ Address not supported");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Connection Failed");
    }

    //creating a new thread for receiving messages from the server
    // one thread is receiving messages
    int ret = pthread_create(&recvThread, NULL, receiveMessage, (void *) sock);
    if (ret) {
     printf("ERROR: Return Code from pthread_create() is %d\n", ret);
     exit(1);
    }

    int username_flag = 0; // 0: username not set
    // sock = (int) socket;
    char buffer[BUF_SIZE] = {0}; // used to read in username
    char username[BUF_SIZE]; // used to store username
    char message_buffer[BUF_SIZE] = {0}; // used to store outgoing message

    if(!username_flag){
      printf("Marauders' Map v1.0\n");
      fgets(buffer, BUF_SIZE, stdin);
      int length = strlen(buffer);
      strncpy(username, buffer, length-1);
      username[length+1] = '\0';
      sprintf(message_buffer, "New user joined: %s\n", username);
      int ret = send(sock, message_buffer, BUF_SIZE, 0);
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
        memset(message_buffer, 0, BUF_SIZE);
        last_loc = location(room_lookup);
        enqueue(last_loc, loc_log);
        initPlayer(last_loc->x, last_loc->y, username, last_loc->level);
        // The string of x, y, floor is stored in message_buffer
        create_message(username, loc_log, message_buffer, BUF_SIZE); // calculate average loc from queue and send it
        int ret = send(sock, message_buffer, BUF_SIZE, 0);
        if(ret < 0) {
          printf("Error sending data");
          exit(1);
        }
        // parse message and update list of user locations
        sleep(5);
    }
    pthread_exit(NULL);
    return NULL;
}
