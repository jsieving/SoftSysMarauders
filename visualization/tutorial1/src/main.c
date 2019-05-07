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
	// initialize client thread

	memset(&app, 0, sizeof(App));

	initSDL();

	// initializing the background image
	app.background.x = 0;
	app.background.y = 0;
	app.background.texture = loadTexture("graphics/wh1.png");

// initializing people (wrap in for loop later)

// room #120 should be x = 1370, y=1280
// room #107 should be x = 440, y=170
// room #114 should be x = 860, y=1790
// initialize the player, based on coordinate position.
// initPlayer() is in entities.c
	Entity *p1 = initPlayer(1370, 1280, NULL);
	Entity *p2 = initPlayer(440, 170, p1);
	Entity *p3 = initPlayer(860, 1790, p2);

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
		blit(app.background.texture, app.background.x, app.background.y, 0, 1);
		drawEntities(p3);

		// blits cursor and writes the scen. Anything blitted afterwards will not present
		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
