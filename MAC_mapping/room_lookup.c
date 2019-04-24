#include "mac_mapping.h"

int main(int argc, char* argv[]) {
  char* filename = NULL;
  if (argc > 1) {
    filename = argv[1];
  }
  GHashTable* room_lookup = make_mapping(filename);
  g_hash_table_foreach(room_lookup, print_room_entry, NULL);
  // g_hash_table_foreach(room_lookup, delete_entry, room_lookup);
  return 0;
}
