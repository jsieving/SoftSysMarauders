#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    char* params[2] = {"scan", NULL};
    // params[0] = "scan";
    // params[1] = NULL;
    // params[1] = "scan";
    // params[2] = ">>"
    // params[3] = "MACs.txt"

    pid_t pid = fork();
    if(pid == -1) {
      fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
      return 1;
    }
    if(pid == 0) {
      if(execv("/sbin/iwlist", params) == -1) {
        fprintf(stderr, "Can't run script: %s\n", strerror(errno));
        return -1;
      }
    }
}
