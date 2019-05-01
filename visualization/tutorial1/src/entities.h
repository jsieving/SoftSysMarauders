#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center, double scale);

extern void initPlayer(int x, int y);
extern SDL_Texture *loadTexture(char *filename);

extern Player *player;
extern App app;
