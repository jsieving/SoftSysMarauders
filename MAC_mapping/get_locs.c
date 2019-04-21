#include "mac_mapping.h"

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
  puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  while (near_rooms[i] != NULL) {
    printf("  Signal strength: %d | ", strength_array[i]);
    print_room(near_rooms[i]);
    i++;
  }
  return 0;
}
