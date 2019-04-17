#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status, exit_status;


    int fd[2];
    if(pipe(fd)==-1) {
      printf("Could not create pipe\n");
    }
    pid_t pid = fork();

    if(pid == -1) {
      fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
      return 1;
    }

    if(pid == 0) { //child
      close(fd[0]);
      dup2(fd[1], 1);

      int res = system("nmcli -f BSSID,SIGNAL -t dev wifi");
      if(res == -1) {
        fprintf(stderr, "Can't run script: %s\n", strerror(errno));
        return -1;
      }
    }

    if(pid > 0) { //parent
      dup2(fd[0], 0);
      close(fd[1]);

      wait(NULL);
      printf("child completed\n");

      char line[255];
      while(fgets(line, 255, stdin)) {
          printf("%s\n", line);
      }

      waitpid(pid, &status, 0);
      if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Exit status of child was %d\n", exit_status);
      }
    }

    return 0;
}
