/*
This is code for drawing people(entities) to the screen
*/

#include "entities.h"

void initPlayer(int x, int y)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
  // adding new player to the end of the list
	app.pTail->next = player;
	app.pTail = player;

	player->texture = loadTexture("graphics/person.png");
	player->x = x;
	player->y = y;

	// SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{

}

void doEntities(void) {
}


void drawEntities(void) {
  // Draws all people using app to the screen

	Player *e;

	for (e = app.pHead->next ; e != NULL ; e = e->next)
	{
    // this is probably where we want to show their names as well
		blit(e->texture, e->x/3, e->y/3, 1, .07);
	}
}
