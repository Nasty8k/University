#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
       
    int kill_num;
    pid_t pid;
    int status;
    
    switch (pid = fork()) {
      case -1:
        perror("fork error!");
        exit(-1);
      case 0:
        printf("PPID[%d], I'm child PID[%d]\n", getppid(), getpid());
        execl("procShow", NULL);
      default:
        printf("PID[%d] It's me, my child is [%d]\n", getpid(), pid);
        printf("I am waiting for child's exit\n");
        wait(&status);
     }
     
    printf("Kill ID number: ");
    scanf("%d", &kill_num);
    
    if (kill(kill_num, SIGKILL)) perror("kill():");
    return 0;
}
