#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mac_mapping.h"

int main(int argc, char const *argv[])
{
    char routers[] = "1810,650,4,37-1820,1110,4,35-1460,810,4,10-";
    char* result = location(routers);
    puts(result);
}
