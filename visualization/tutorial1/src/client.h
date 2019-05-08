#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include "mac_mapping.h"
#include "common.h"



// from visualization

extern Entity* initPlayer(int x, int y, char* name, int floor);

extern App app;
