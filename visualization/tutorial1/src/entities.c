/*
This is code for drawing people(entities) to the screen
*/

#include "entities.h"

Entity* initPlayer(int x, int y, char* name, int f)
{
	Entity* player = malloc(sizeof(Entity));
	// memset(&player, 0, sizeof(Entity));

	player->texture = loadTexture("graphics/person.png");
	player->x =(int) (x/2.86)+110;
	player->y =(int) (y/2.86)+14;

	char* n = malloc(strlen(name)+1);
	n = name;
	player->name = n;
	player->floor = f;

	//pushing new player to beginning of list
	player->next = app.head;
	app.head = player;
	return player;
}

void readClicks(void)
{
	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		// get the coordinates of the mouse when it was clicked
		int x = app.mouse.x;
		int y = app.mouse.y;

		// hardcode the coordinates of all the boxes
		if( ( x > 90 ) && ( x < 220 ) && ( y > 237 ) && ( y < 300 ) ){
			//change the background.texture to the floor that was clicked on
			app.background.texture = loadTexture("graphics/wh1.png");
		}
		if( (x > 90) && ( x < 220) && (y > 320) && (y < 400)){
			app.background.texture = loadTexture("graphics/wh2.png");
		}
		if( (x > 90) && ( x < 220) && (y > 420) && (y < 500)){
			app.background.texture = loadTexture("graphics/wh3.png");
		}
		if( (x > 90) && ( x < 220) && (y > 520) && (y < 600)){
			app.background.texture = loadTexture("graphics/wh4.png");
		}

		app.mouse.button[SDL_BUTTON_LEFT] = 0;
	}

}

void doEntities(void) {
}


void drawEntities() {
  // Draws all people using app to the screen
	TTF_Font* HP = TTF_OpenFont("graphics/hp.TTF", 24); //this opens a font style and sets a size
	SDL_Color Black = {0,0,0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	// Blit the person image
	Entity *e;

	for (e = app.head; e != NULL ; e = e->next)
	{
    // shows the person figure
		blit(e->texture, e->x, e->y, e->name, 1, .07);

		// // shows the name
		// SDL_Surface* surfaceMessage = TTF_RenderText_Solid(HP, e->name, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
		//
		// SDL_Texture* Message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage); //now you can convert it into a texture
		//
		// SDL_Rect Message_rect; //create a rect
		// Message_rect.x = e->x;  //controls the rect's x coordinate
		// Message_rect.y = e->y; // controls the rect's y coordinte
		// Message_rect.w = 100; // controls the width of the rect
		// Message_rect.h = 100; // controls the height of the rect
		//
		// //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance
		//
		// //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
		//
		// SDL_RenderCopy(app.renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
		//
		// //Don't forget too free your surface and texture
	}
}
