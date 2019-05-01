/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "main.h"

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&background, 0, sizeof(Entity));
	// memset(&player, 0, sizeof(Player));

	initSDL();

	// initializing the background image
	background.x = -100;
	background.y = 0;
	background.texture = loadTexture("graphics/footprints.jpg");

	// player->x = -100;
	// player->y = 0;
	// player->texture = loadTexture("graphics/person.png");

	atexit(cleanup);

	// initGame();
	initStage();
	// initPlayer(500,500);

	while (1)
	{
		prepareScene();

		// adding background image to screen, comes after prepare scene
		blit(background.texture, background.x, background.y, 0, 1.1);

		// adding background image to screen, comes after prepare scene
		// blit(player->texture, player->x, player->y, 0, .07);

		doInput();

		// where the mouse logic happens
		app.delegate.logic(); // does nothing at the moment
		app.delegate.draw(); // draws mouse icon, and players

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
