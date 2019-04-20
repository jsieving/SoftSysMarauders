#include <glib.h>
#include <glib/gstdio.h>
// #include <fcntl.h>

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
  room->room_num = room_num;
  room->level = level;
  room->x = x;
  room->y = y;
  return room;
}

// frees a Room.
void free_room(void* room) {
  free((Room*)room);
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
  char* room_num;
  int level;
  int x = 0;
  int y = 0;
  Room* room;
  while (lines[i] != NULL) {
    if (lines[i][0] == 'W') {
      room_num = lines[i];
      level = atoi(lines[i][3]);
      room = make_room(room_num, level, x, y);
      g_hash_table_insert(room_lookup, lines[i+1], room);
      g_hash_table_insert(room_lookup, lines[i+2], room);
      i += 3;
    } else { i++; }
  }
  g_strfreev (lines);
  return 0;
}
