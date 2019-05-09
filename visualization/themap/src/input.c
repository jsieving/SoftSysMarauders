/*
Monitors user input. Registers when the mouse moves/is clicked, and when the window is closed.

*/

#include "input.h"
//
// void doMouseButtonDown(SDL_MouseButtonEvent *event)
// { // link mouse click event to function of buttons
// 	app.mouse.button[event->button] = 1;
// }
void doMouseButtonUp(SDL_MouseButtonEvent *event)
{
	app.mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent *event)
{
	app.mouse.button[event->button] = 1;
}

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

			case SDL_MOUSEBUTTONDOWN:
				doMouseButtonDown(&event.button);
				break;

			case SDL_MOUSEBUTTONUP:
				doMouseButtonUp(&event.button);
				break;

			default:
				break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}
