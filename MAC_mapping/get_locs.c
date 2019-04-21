#include "mac_mapping.h"

void get_near_rooms(Room** room_array, int* strength_array, int max_rooms) {
  int scan_length = 20;
  char* mac_array[scan_length+1];
  mac_array[scan_length] = "\0";
  int s_array[scan_length+1];
  s_array[scan_length] = 0;
  get_macs_strength(mac_array, s_array, scan_length);

  char* filename = "MAC_rooms.txt";
  GHashTable* room_lookup = make_mapping(filename);
  // g_hash_table_foreach(room_lookup, print_room_entry, NULL);

  int i = 0;
  int n = 0;
  Room* room;
  while (mac_array[i] != NULL && n < max_rooms && n <= i) {
    room = (Room*) g_hash_table_lookup(room_lookup, (gchar*) mac_array[i]);
    if (room == NULL) {
      printf("Not a key: %s\n", mac_array[i]);
      error("Error in get_near_rooms: room lookup failed.");
    }
    room_array[n] = room;
    strength_array[n] = s_array[i];
    n++;
    i++;
  }
}

int main(int argc, char *argv[]) {
  int max_rooms;
  if (argc > 1) {
    max_rooms = atoi(argv[1]);
  } else {
    max_rooms = 3;
  }

  Room* near_rooms[max_rooms+1];
  near_rooms[max_rooms] = NULL;
  int strength_array[max_rooms];
  get_near_rooms(near_rooms, strength_array, max_rooms);
  int i = 0;
  while (near_rooms[i] != NULL) {
    printf("Signal strength: %d | ", strength_array[i]);
    print_room(near_rooms[i]);
    i++;
  }
  return 0;
}
