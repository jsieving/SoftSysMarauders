#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center, double scale);

extern void drawEntities(Entity* list);
extern Entity* initPlayer(int x, int y, Entity* next);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern App app;
