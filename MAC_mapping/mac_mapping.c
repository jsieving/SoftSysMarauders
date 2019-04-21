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

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void get_macs_strength(char** mac_array, int* strength_array, int length) {
  int status;

  int fd[2];
  if(pipe(fd)==-1) {
    printf("Could not create pipe\n");
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
          printf("Process %d exited unsuccessfully with error code %d.\n", pid, status);
      }
    }
  }
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

GHashTable* make_mapping(char* filename) {
  GHashTable* room_lookup = g_hash_table_new(g_str_hash, g_str_equal);
  gchar *text; // text from file
  gchar **lines; // list of lines
  GError* error; // error buffer
  gchar* split = "\n";

  if (!filename) {
    filename = "MAC_rooms.txt";
  }
  // read the file contents and check that this was successful
  gboolean res = g_file_get_contents(filename, &text, NULL, &error);
  if (res == 0) {
    puts("Error in main: g_file_get_contents: failed to read file.");
    exit(1);
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
    if (lines[i][0] == 'W') { // Quick and dirty for WH rooms
      room_num = lines[i];
      level = atoi(&(lines[i][3])) / 100;
      // x = atoi(&(lines[i+3][3])) // below MACs: 'x: 000'
      // y = atoi(&(lines[i+4][3])) // below MACs: 'y: 000'
      room = make_room(room_num, level, x, y);
      char* MAC1 = strndup(lines[i+1], 16);
      char* MAC2 = strndup(lines[i+2], 16);
      g_hash_table_insert(room_lookup, MAC1, room);
      g_hash_table_insert(room_lookup, MAC2, room);
      i += 3; // 5
    } else { i++; }
  }
  g_strfreev (lines);
  return room_lookup;
}
