/*
Runs the program. Creates a client thread, calls the initialization functions, and then calls the functions that run the app in a while loop.
*/

#include "main.h"

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));


/////////////////// socket creation ///////////////////
// 	struct sockaddr_in serv_addr;
// 	char * serverAddr;
// 	SDL_Thread * recvThread;
// 	char* ip;
//
// 	if (catch_signal(SIGINT, handle_shutdown) == -1) {
// 			error("Signal catcher setup failed. Setting interrupt handler"); }
//
// 	if (ip != NULL) { //checks that user input server ip address
// 		serverAddr = (char*) ip; //to get server ip address from command line
// 	} else {
// 		serverAddr = "127.0.0.1";
// 		printf("Server ip address not specified. Set to %s.\n", serverAddr);
// 	}
//
// 	if ((app.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
// 	{
// 			error("Socket creation error");
// 	}
//
// 	memset(&serv_addr, '0', sizeof(serv_addr));
//
// 	serv_addr.sin_family = AF_INET;
// 	serv_addr.sin_addr.s_addr = inet_addr(serverAddr);
// 	serv_addr.sin_port = htons(PORT);
//
// 	// Convert IPv4 and IPv6 addresses from text to binary form
// 	if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
// 	{
// 			printf("\nInvalid address/ Address not supported \n");
// 			return -1;
// 	}
//
// 	if (connect(app.sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
// 	{
// 			printf("\nConnection Failed \n");
// 			return -1;
// 	}
// 	/////////////////////////////////////
//
// 	int ret;
//
// 	//creating a new thread for receiving messages from the server
// 	// one thread is receiving messages
// 	recvThread = SDL_CreateThread((SDL_ThreadFunction) receiveMessage, "receiver", (void *) app.sock);
// 	if (NULL == recvThread) {
// 	 printf("SDL_CreateThread failed: %s\n", SDL_GetError());
// 	}
//
// // create client thread
// 	// char* ip = "127.0.0.1";
// 	app.thread = SDL_CreateThread( (SDL_ThreadFunction) run_client, "client_thread", (void *) app.sock);
//
// 	if (NULL == app.thread) {
// 		printf("SDL_CreateThread failed: %s\n", SDL_GetError());
// 	}
	// else {
	// 		SDL_WaitThread(app.thread, &ret);
	// 		printf("Thread returned value: %d\n", ret);
	// }

	// while(app.start != 1){}

	// puts("App started");
	initSDL();

	// initializing the background image
	app.background.x = 0;
	app.background.y = 0;
	app.background.texture = loadTexture("graphics/wh1.png");
	app.floor = 1;

// initializing people (wrap in for loop later)

// initialize the player, based on coordinate position.
// initPlayer() is in entities.c
Entity *p1 = initPlayer(790, 1440, "Jane", 3);
Entity *p2 = initPlayer(900, 950, "Allen", 2);
Entity *p3 = initPlayer(1370, 1280, "Emma", 1);
Entity *p4 = initPlayer(1460, 810, "Ashley", 4);

// removePlayer("boi");

	atexit(cleanup);

	// initialize the mouse
	initCursor();

	while (1)
	{
		prepareScene();

		// mouse logic goes here
		doInput();

		// App draw functions called where
		readClicks();

		// adding background image to screen, comes right after prepare scene
		blit(app.background.texture, app.background.x, app.background.y, NULL, 0, 1);
		drawEntities();

		// blits cursor and writes the scen. Anything blitted afterwards will not present
		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
