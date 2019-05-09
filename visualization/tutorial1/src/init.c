/*
Initializes the framework and necessary components, then creates and opens a window.

Also includes cleanup functions for ending the program.

*/

#include "init.h"

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	TTF_Init();

	app.window = SDL_CreateWindow("Marauder's Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	// make sure the native cursor is off
	SDL_ShowCursor(0);
}

// initializing the stage, with the mouse graphics:
static SDL_Texture *targetterTexture;

void initCursor(void)
{	// initialize the cursor image
	app.mouse.texture = loadTexture("graphics/wand.png");
}

void cleanup(void)
{
	//Stop the thread
	// SDL_KillThread(app.thread);

	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	TTF_Quit();

	SDL_Quit();
}
