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

void doPlayer(void)
{

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
