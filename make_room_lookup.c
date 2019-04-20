#include <glib.h>
#include <glib/gstdio.h>

// a room and its location.
typedef struct {
  gchar* room_num;
  gint level;
  gint x;
  gint y;
} Room;

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

void print_room(gpointer key, gpointer value, void* data) {
  gchar* MAC = (gchar*) key;
  Room* room = (Room*) value;
  printf("%s ==> %s\n", MAC, room->room_num);
}

int main(int argc, char* argv[]) {
  GHashTable* room_lookup = g_hash_table_new(g_str_hash, g_str_equal);
  gchar *filename;
  gchar *text; // text from file
  gchar **lines; // list of lines
  GError* error; // error buffer
  gchar* split = "\n";

  if (argc > 1) {
    filename = argv[1];
  } else {
    filename = "MAC_rooms.txt";
  }

  // read the file contents and check that this was successful
  gboolean res = g_file_get_contents(filename, &text, NULL, &error);
  if (res == 0) {
    puts("Error in main: g_file_get_contents: failed to read file.");
    return 1;
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
      room = make_room(room_num, level, x, y);
      char* MAC1 = strndup(lines[i+1], 17);
      char* MAC2 = strndup(lines[i+2], 17);
      g_hash_table_insert(room_lookup, MAC1, room);
      g_hash_table_insert(room_lookup, MAC2, room);
      i += 3;
    } else { i++; }
  }
  g_hash_table_foreach(room_lookup, print_room, NULL);
  g_strfreev (lines);
  return 0;
}
