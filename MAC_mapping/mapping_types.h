#include <stdlib.h>
#include <sys/types.h>

typedef struct {
  int level;
  int x;
  int y;
  int strength;
  Record* next;
  Record* prev;
} Record;
