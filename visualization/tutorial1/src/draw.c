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
	blit(app.mouse.texture, app.mouse.x, app.mouse.y, NULL, 1, .7);
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y, char* name, int center, double scale)
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

	TTF_Font* HP = TTF_OpenFont("graphics/hp.TTF", 100); //this opens a font style and sets a size
	SDL_Color Black = {0,0,0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	// name Code	// shows the name
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(HP, name, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage); //now you can convert it into a texture


// SDL_RenderCopy takes four parameters: the renderer, texture, rectangular regions of the src texture and the target renderer.
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);

	dest.y += dest.h/2;
	dest.h = 40;
	dest.w = 40;
	if(name != NULL){
		dest.w = (int)((strlen(name)) * 20);
		dest.x = x-dest.w/2;
	}

	SDL_RenderCopy(app.renderer, Message, NULL, &dest);

	// clean up text rendering tools
	TTF_CloseFont(HP);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

// static void draw_cursor(void)
// {
// 	blit(app.mouse.texture, app.mouse.x, app.mouse.y, 1, .7);
// }
