/*
Runs the program. Creates a client thread, calls the initialization functions, and then calls the functions that run the app in a while loop.
*/

#include "main.h"

int main(int argc, char *argv[])
{
	initSDL();
	memset(&app, 0, sizeof(App));

	XInitThreads();
	int ret;


// create client thread
	char* ip = "127.0.0.1";
	app.thread = SDL_CreateThread( (SDL_ThreadFunction) run_client, "client_thread", (void *) ip);

	if (NULL == app.thread) {
		printf("SDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
			SDL_WaitThread(app.thread, &ret);
			printf("Thread returned value: %d\n", ret);
	}

	// while(app.start != 1){}

	puts("App started");

	// initializing the background image
	app.background.x = 0;
	app.background.y = 0;
	app.background.texture = loadTexture("graphics/wh1.png");
	app.floor = 1;

// initializing people (wrap in for loop later)

// room #120 should be x = 1370, y=1280
// room #107 should be x = 440, y=170
// room #114 should be x = 860, y=1790
// initialize the player, based on coordinate position.
// initPlayer() is in entities.c
Entity *p1 = initPlayer(1370, 1280, "boi", 3);
Entity *p2 = initPlayer(440, 170, "sup", 2);
Entity *p3 = initPlayer(860, 1790, "hi", 1);
Entity *p4 = initPlayer(1000, 1500, "boo", 4);
removePlayer("boi");

	atexit(cleanup);

	// initialize the mouse
	initCursor();

	while (1)
	{
		prepareScene();

		// App logic functions called here, before doInput()

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
