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

typedef struct Player Player;

typedef struct {
	int x;
	int y;
} Mouse;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

// For drawing images
typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

struct Player{
	int x;
	int y;
	char* name;
	SDL_Texture *texture;
	Player *next;
};

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	Mouse mouse;
	Player *pHead, *pTail; // for the list of users
} App;
