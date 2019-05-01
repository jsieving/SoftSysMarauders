#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <glib.h>
#include <glib/gstdio.h>

extern int ERRORS_ON;

void error(char *msg);
int get_macs_strength(char** mac_array, int* strength_array, int length);

// a room and its location.
typedef struct {
  gchar* room_num;
  gint level;
  gint x;
  gint y;
} Room;

// creates a Room.
Room* make_room(gchar* room_num, gint level, gint x, gint y);
// frees a Room.
void free_room(void* room);
// frees and deletes a hashtable entry.
void delete_entry(void* key, void* value, void* table);

void print_room(Room* room);

void print_room_entry(void* key, void* value, void* data);

GHashTable* make_mapping(char* filename);

int get_near_rooms(GHashTable* room_lookup, Room** room_array, int* strength_array, int max_rooms);

int create_message(GHashTable* room_lookup, char* buffer, int buf_len);

char* location(char* input);
