/*
Includes code for initializing an entity when a new player joins, 
removing and updating players,
changing the background based on mouse clicks for different floors,
and calling draw functions to show the relevant players on the screen.
*/

#include "entities.h"

Entity* initPlayer(int x, int y, char* name, int f){
	/*
	Initializes a new player entity, given x, y, name, and floor number
	Appends the player to the beginning of the list, whose first pointer is stored in app.head
	*/
	Entity* player = malloc(sizeof(Entity));
	// memset(&player, 0, sizeof(Entity));

	player->texture = loadTexture("graphics/person.png");
	player->x =(int) (x/2.86)+110;
	player->y =(int) (y/2.86)+14;

	char* n = malloc(strlen(name)+1);
	n = name;
	player->name = n;
	player->floor = f;

	// initialize floor as the texture for the background
	// char temp[17];
	// snprintf(temp, 17, "graphics/wh%i.png", f);
	// SDL_Texture* tex = loadTexture(temp);
	// player->floor = tex;

	//pushing new player to beginning of list
	player->next = app.head;
	app.head = player;
	return player;
}

Entity* removePlayer(char* name) {
	/*
	Finds and removes a player entity by name.
	Returns the removed Entity object.
	*/
  Entity * this = (Entity*) app.head;

  // make sure the first node isn't the match
  if(strcmp(this->name, name) == 0){
		Entity* save = this;
		app.head = this->next;
    return this;
  }
  while(this->next != NULL){
		Entity *next = this->next;
    if(strcmp(next->name, name) == 0){
      Entity *temp = next;
      this->next = next->next;
      // free(temp);
      return temp;
    }
    this = this->next;
  }
  return 0;
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
			app.floor = 1;
		}
		if( (x > 90) && ( x < 220) && (y > 320) && (y < 400)){
			app.background.texture = loadTexture("graphics/wh2.png");
			app.floor = 2;
		}
		if( (x > 90) && ( x < 220) && (y > 420) && (y < 500)){
			app.background.texture = loadTexture("graphics/wh3.png");
			app.floor = 3;
		}
		if( (x > 90) && ( x < 220) && (y > 520) && (y < 600)){
			app.background.texture = loadTexture("graphics/wh4.png");
			app.floor = 4;
		}

		app.mouse.button[SDL_BUTTON_LEFT] = 0;
	}

}

void drawEntities() {
  // Draws all people using app to the screen
	// Blit the person image
	Entity *e;

	for (e = app.head; e != NULL ; e = e->next)
	{
    // show the person if you're on the floor that they're on
		if(e->floor == app.floor){
			blit(e->texture, e->x, e->y, e->name, 1, .07);
		}
	}
}
