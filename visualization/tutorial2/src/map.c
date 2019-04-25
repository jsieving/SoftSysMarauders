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

#include "map.h"

static void loadTiles(void);
static void loadMap(const char *filename);

static SDL_Texture *tiles[MAX_TILES];

void initMap(void)
{
	memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
	
	loadTiles();
	
	loadMap("data/map01.dat");
}

void drawMap(void)
{
	int x, y, n;
	
	for (y = 0 ; y < MAP_RENDER_HEIGHT ; y++)
	{
		for (x = 0 ; x < MAP_RENDER_WIDTH ; x++)
		{
			n = stage.map[x][y];
			
			if (n > 0)
			{
				blit(tiles[n], x * TILE_SIZE, y * TILE_SIZE, 0);
			}
		}
	}
}

static void loadTiles(void)
{
	int i;
	char filename[MAX_FILENAME_LENGTH];
	
	for (i = 1 ; i <= MAX_TILES ; i++)
	{
		sprintf(filename, "gfx/tile%d.png", i);
		
		tiles[i] = loadTexture(filename);
	}
}

static void loadMap(const char *filename)
{
	char *data, *p;
	int x, y;
	
	data = readFile(filename);
	
	p = data;
	
	for (y = 0 ; y < MAP_HEIGHT ; y++)
	{
		for (x = 0 ; x < MAP_WIDTH ; x++)
		{
			sscanf(p, "%d", &stage.map[x][y]);
			
			do {p++;} while (*p != ' ' && *p != '\n');
		}
	}
	
	free(data);
}
