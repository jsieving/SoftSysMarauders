#include "mac_mapping.h"

int main() {
    int length = 20;
    char* mac_array[length+1];
    mac_array[length] = "\0";
    int strength_array[length];
    get_macs_strength(mac_array, strength_array, length);
    int n = 0;
    while (mac_array[n] != NULL) {
      printf("%s | %d\n", mac_array[n], strength_array[n]);
      n++;
    }
    return 0;
}
