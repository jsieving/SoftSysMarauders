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

// a room and its location.
typedef struct {
  gchar* room_num;
  gint level;
  gint x;
  gint y;
} Room;

typedef struct {
  int level;
  int x;
  int y;
  void* next;
  void* prev;
} Record;

typedef struct {
  Record* head;
  Record* tail;
  int size;
  int max_size;
  int total_x;
  int total_y;
  int last_level;
} Queue;

void error(char *msg);

int get_macs_strength(char** mac_array, int* strength_array, int length);

// creates a Room.
Room* make_room(gchar* room_num, gint level, gint x, gint y);
// frees a Room.
void free_room(void* room);
// frees and deletes a hashtable entry.
void delete_entry(void* key, void* value, void* table);

void print_room(Room* room);

void print_room_entry(void* key, void* value, void* data);
// creates a Record of triangulated location.
Record* make_record(int x, int y, int level, Record* prev, Record* next);
// frees a Record.
void free_record(void* record);

void print_record(Record* record);
// Creates a queue with the given max size.
Queue* make_queue(int max_size);
// frees a Queue, and all associated Records.
void free_queue(void* queue);
// prints a Queue, and all associated Records.
void print_queue(Queue* queue);
// perhaps poorly named... adds a Record to the head of a Queue,
// and if the queue has exceeded its size limit, dequeues from the tail
void enqueue(Record* new, Queue* queue);

GHashTable* make_mapping(char* filename);

int get_near_rooms(GHashTable* room_lookup, Room** room_array, int* strength_array, int max_rooms);

Record* location(GHashTable* room_lookup);

int create_message(Queue* queue, char* buffer, int buf_len);
