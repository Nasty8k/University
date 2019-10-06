#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
       
    pid_t pid;
        
    switch (pid = fork()) {
      case -1:
        perror("fork error!");
        exit(-1);
      case 0:
        printf("PID[%d], writing..\n", getpid());
        execl("write_to_FIFO", NULL);
      default:
        printf("PID[%d] reading..\n", getpid());
        execl("read_from_FIFO", NULL);
     }
    return 0;
}
