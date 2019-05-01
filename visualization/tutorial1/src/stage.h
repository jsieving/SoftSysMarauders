#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center, double scale);

// functions for drawing players
extern void doEntities(void);
extern void doPlayer(void);
extern void drawEntities(void);
extern void initPlayer(int x, int y);

extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Player *player;
