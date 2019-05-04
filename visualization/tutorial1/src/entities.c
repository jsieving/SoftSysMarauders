/*
This is code for drawing people(entities) to the screen
*/

#include "entities.h"

Entity* initPlayer(int x, int y, Entity* next)
{
	Entity* player = malloc(sizeof(Entity));
	// memset(&player, 0, sizeof(Entity));

	player->texture = loadTexture("graphics/person.png");
	player->x =(int) (x/2.86)+110;
	player->y =(int) (y/2.86)+14;

	//pushing new player to beginning of list
	player->next = next;
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
		if( ( x > 0 ) && ( x < 500 ) && ( y > 0 ) && ( y < 500 ) ){
			//change the background.texture to the floor that was clicked on
			app.background.texture = loadTexture("graphics/fake.jpeg");
		}
		else{
			app.background.texture = loadTexture("graphics/footprints.jpg");
		}

		app.mouse.button[SDL_BUTTON_LEFT] = 0;
	}

}

void doEntities(void) {
}


void drawEntities(Entity* list) {
  // Draws all people using app to the screen

	Entity *e;

	for (e = list; e != NULL ; e = e->next)
	{
    // this is probably where we want to show their names as well
		blit(e->texture, e->x, e->y, 1, .07);
	}
}
