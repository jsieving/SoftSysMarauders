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

#include "input.h"
//
// void doMouseButtonDown(SDL_MouseButtonEvent *event)
// { // link mouse click event to function of buttons
// 	app.mouse.button[event->button] = 1;
// }


void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			// case SDL_MOUSEBUTTONDOWN:
			// 	doMouseButtonDown(&event.button);
			// 	break;

			default:
				break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}
