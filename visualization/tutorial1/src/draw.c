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

#include "draw.h"

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y, int center, double scale)
/*Draws the specified texture on screen at the specified x and y coordinates.
	if center = 1: center the picture
	else: blit by the upper right corner
*/
{
	SDL_Rect dest;

	// This puts in the coordinates from where the texture should be drawn
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	// this scales the image!
	dest.w = dest.w*scale;
	dest.h = dest.h*scale;

// SDL_RenderCopy takes four parameters: the renderer, texture, rectangular regions of the src texture and the target renderer.
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
