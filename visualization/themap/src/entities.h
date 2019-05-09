#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, char* name, int center, double scale);

extern void drawEntities();
extern Entity* initPlayer(int x, int y, char* name, int floor);
extern Entity* removePlayer(char* name);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern App app;
