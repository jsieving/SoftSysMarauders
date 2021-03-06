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


typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
	int button[6]; // not sure why it's 6... maybe 6 types of button states?
} Mouse;

// For drawing images
typedef struct {
	int x;
	int y;
	char* name;
	int floor;
	SDL_Texture *texture;
	struct Entity *next;
} Entity;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Mouse mouse;
	Entity background;
	struct Entity *head; // keeps track of head of the players list
	int floor; // keeps track of which floor you're on
	int start;
	int sock; // used by sending (parent) thread
	//Quit flag
	int quit; // 0 is false, 1 is true
	SDL_Thread *thread;
} App;
