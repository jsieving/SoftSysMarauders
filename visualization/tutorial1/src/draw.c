/*
This file includes the functions related to displaying graphics on the screen:
	- prepareScene(void) : 
*/

#include "draw.h"

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	SDL_RenderClear(app.renderer);

}

void presentScene(void)
{
	blit(app.mouse.texture, app.mouse.x, app.mouse.y, 1, .7);
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

	// this scales the image!
	dest.w = dest.w*scale;
	dest.h = dest.h*scale;

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

// SDL_RenderCopy takes four parameters: the renderer, texture, rectangular regions of the src texture and the target renderer.
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

// static void draw_cursor(void)
// {
// 	blit(app.mouse.texture, app.mouse.x, app.mouse.y, 1, .7);
// }
