#include "stage.h"

static void logic(void);
static void draw(void);

static SDL_Texture *targetterTexture;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	// initialize the cursor image
	targetterTexture = loadTexture("graphics/wand.png");
}

static void logic(void)
{
	// draw all the people
	// doEntities();

}

static void draw(void)
{
	// drawEntities();
	blit(targetterTexture, app.mouse.x, app.mouse.y, 1, .7);
}
