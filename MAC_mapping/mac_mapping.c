#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <glib.h>
#include <glib/gstdio.h>
#include "mac_mapping.h"

int ERRORS_ON = 0;

void error(char *msg)
{
    if (ERRORS_ON) {fprintf(stderr, "%s: %s\n", msg, strerror(errno));}
    exit(1);
}

int get_macs_strength(char** mac_array, int* strength_array, int length) {
  int status;

  int fd[2];
  if(pipe(fd)==-1) {
    error("Could not create pipe");
  }
  pid_t pid = fork();

  if(pid == -1) {
    error("Can't fork process.");
  }

  if(pid == 0) { //child
    close(fd[0]);
    dup2(fd[1], 1);
    int res = system("nmcli -f BSSID,SIGNAL -t -e no dev wifi");
    if(res == -1) {
      error("Error when running program 'nmcli'.");
    }
    exit(0);
  }

  if(pid > 0) { //parent
    dup2(fd[0], 0);
    close(fd[1]);

    pid = wait(&status);
    // check for an error in wait
    if (pid == -1) {
        error("Wait failed.");
    }

    char line[24];
    int strength;
    int num = 0;
    char mac[16];
    while(fgets(line, 24, stdin) && num < length) {
      sscanf(line, "%17s:%2d", mac, &strength);
      mac[16] = '\0';
      mac_array[num] = strdup(mac);
      strength_array[num] = strength;
      num++;
    }

    if (WIFEXITED(status)) {
      status = WEXITSTATUS(status);
      if (status) { // if a process did not exit normally
          char msg[80];
          sprintf(msg, "Process %d exited unsuccessfully with error code %d.", pid, status);
          error(msg);
      }
    }
    return num;
  }
  return 0;
}

// creates a Room.
Room* make_room(gchar* room_num, gint level, gint x, gint y) {
  Room* room = malloc(sizeof(Room));
  room->room_num = strndup(room_num, 6);
  room->level = level;
  room->x = x;
  room->y = y;
  return room;
}

// frees a Room.
void free_room(void* room) {
  Room * r = (Room*) room;
  free(r->room_num);
  free(room);
}

// frees and deletes a hashtable entry.
void delete_entry(void* key, void* value, void* table) {
  GHashTable* lookup = (GHashTable*) table;
  g_hash_table_remove(key, lookup);
  gchar* MAC = (gchar*) key;
  Room* room = (Room*) value;
  free(MAC);
  free_room(room);
}

void print_room(Room* room) {
  printf("%s, level %d, (%d, %d)\n", room->room_num, room->level, room->x, room->y);
}

void print_room_entry(void* key, void* value, void* data) {
  gchar* MAC = (gchar*) key;
  Room* room = (Room*) value;
  printf("%s ==> %s, level %d, (%d, %d)\n", MAC, room->room_num, room->level, room->x, room->y);
}

// creates a Record of triangulated location.
Record* make_record(int x, int y, int level, Record* prev, Record* next) {
  Record* record = malloc(sizeof(Record));
  record->x = x;
  record->y = y;
  record->level = level;
  record->prev = prev;
  record->next = next;
  return record;
}

// frees a Record.
void free_record(void* record) {
  free(record);
}

void print_record(Record* record) {
  printf("(%d, %d), level %d\n", record->x, record->y, record->level);
}

// Creates a queue with the given max size.
Queue* make_queue(int max_size) {
  Queue* queue = malloc(sizeof(Queue));
  queue->size = 0;
  queue->max_size = max_size;
  queue->total_x = 0;
  queue->total_y = 0;
  return queue;
}

// frees a Queue, and all associated Records.
void free_queue(void* queue) {
  Queue* q = (Queue*) queue;
  Record* curr = q->head;
  Record* next;
  while(curr) {
    next = curr->next;
    free_record(curr);
    curr = next;
  }
  free(queue);
}

// prints a Queue, and all associated Records.
void print_queue(Queue* queue) {
  Record* curr = queue->head;
  Record* next;
  printf("Queue: full %d/%d\n", queue->size, queue->max_size);
  printf("Total X: %d; total Y: %d\n", queue->total_x, queue->total_y);
  while(curr) {
    next = curr->next;
    print_record(curr);
    curr = next;
  }
}

// perhaps poorly named... adds a Record to the head of a Queue,
// and if the queue has exceeded its size limit, dequeues from the tail
void enqueue(Record* new, Queue* queue) {
  new->next = queue->head;
  if (queue->size == 0) {
    queue->tail = new;
  } else {
    queue->head->prev = new;
  }
  queue->head = new;
  queue->size++;
  queue->total_x += new->x;
  queue->total_y += new->y;
  queue->last_level = new->level;
  if (queue->size > queue->max_size) {
    Record* nexttolast = (Record*) queue->tail->prev;
    nexttolast->next = NULL;
    queue->total_x -= queue->tail->x;
    queue->total_y -= queue->tail->y;
    queue->size--;
    free_record(queue->tail);
    queue->tail = nexttolast;
  }
}

GHashTable* make_mapping(char* filename) {
  GHashTable* room_lookup = g_hash_table_new(g_str_hash, g_str_equal);
  gchar *text; // text from file
  gchar **lines; // list of lines
  GError* err_buf; // error buffer
  gchar* split = "\n";

  if (!filename) {
    filename = "MAC_rooms.txt";
  }
  // read the file contents and check that this was successful
  gboolean res = g_file_get_contents(filename, &text, NULL, &err_buf);
  if (res == 0) {
    error("Error in make_mapping-> g_file_get_contents-> failed to read file");
  }

  // split the text into lines
  lines = g_strsplit(text, split, 0);
  int i = 0;
  gchar* room_num;
  gint level;
  gint x = 0;
  gint y = 0;
  Room* room;
  while (lines[i] != NULL) {
    if (lines[i][0] == '>') {
      room_num = &(lines[i][1]);
      level = atoi(&(lines[i][4])) / 100;
      x = atoi(&(lines[i+3][2])); // below MACs: 'x:000'
      y = atoi(&(lines[i+4][2])); // below MACs: 'y:000'
      room = make_room(room_num, level, x, y);
      char* MAC1 = strndup(lines[i+1], 16);
      char* MAC2 = strndup(lines[i+2], 16);
      g_hash_table_insert(room_lookup, MAC1, room);
      g_hash_table_insert(room_lookup, MAC2, room);
      i += 5; // if adding x, y lines
    } else { i++; }
  }
  g_strfreev (lines);
  return room_lookup;
}

int get_near_rooms(GHashTable* room_lookup, Room** room_array, int* strength_array, int max_rooms) {
  int max_scan_length = 20;
  char* mac_array[max_scan_length+1];
  int s_array[max_scan_length];
  int result_length = get_macs_strength(mac_array, s_array, max_scan_length);
  mac_array[result_length] = "\0";

  int i = 0;
  int n = 0;
  Room* room;
  while (mac_array[i] != NULL && n < max_rooms && n <= i) {
    room = (Room*) g_hash_table_lookup(room_lookup, (gchar*) mac_array[i]);
    if (room == NULL) {
      if (ERRORS_ON) {
        fprintf(stderr, "\nError in get_near_rooms: room lookup failed.");
        fprintf(stderr, " Not a key: %s\n", mac_array[i]);
      }
    } else {
      int c = 0;
      int exists = 0;
      while (room_array[c] != NULL) {
        if (room_array[c] == room) {
          exists = 1;
        }
        c++;
      }
      if (!exists) {
        room_array[n] = room;
        strength_array[n] = s_array[i];
        n++;
      }
    }
    i++;
  }
  room_array[n] = NULL;
  return n;
}

/* takes in a char array representing 3 nearest routers and returns a char array
representing the triangulated x, y coordinates and floor */
Record* location(GHashTable* room_lookup) {
    int rooms;
    int max_rooms = 3;
    Room* near_rooms[max_rooms+1];
    near_rooms[max_rooms] = NULL;
    int strength_array[max_rooms];
    int tot_strength = 0;
    int avg_x = 0;
    int avg_y = 0;
    int best_level;
    int max_strength = 0;

    rooms = get_near_rooms(room_lookup, near_rooms, strength_array, max_rooms);

    if (rooms < max_rooms && ERRORS_ON) {
      printf("Warning in create_message: %d locations returned by get_near_rooms, %d expected.\n", rooms, max_rooms);
    }
    int i = 0;
    while (near_rooms[i] != NULL) {
      tot_strength += strength_array[i];
      avg_x += near_rooms[i]->x * strength_array[i];
      avg_y += near_rooms[i]->y * strength_array[i];
      if (strength_array[i] > max_strength) {
        max_strength = strength_array[i];
        best_level = near_rooms[i]->level;
      }
      i++;
    }

    avg_x /= tot_strength;
    avg_y /= tot_strength;

    return make_record(avg_x, avg_y, best_level, NULL, NULL);
}

int create_message(Queue* queue, char* buffer, int buf_len) {
  int x = queue->total_x/queue->size;
  int y = queue->total_y/queue->size;
  int level = queue->last_level;

  int n = snprintf(buffer, buf_len, "%d, %d, %d\r\n", x, y, level);

  return n;
}
