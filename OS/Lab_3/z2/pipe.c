#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

int main(void) {

    int fd[2], status;
    int fileSize = 0, totalFileSize = 1;
    char    string[64] = "\0", strsearch[64] = "\0", buf[128] = {"\0"};
    char    readbuf[64];
    pid_t childID, endID;
    time_t when;
    FILE *fp;

    pipe(fd);
    childID = fork();
    
    switch(childID) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
      case 0:
        close(fd[0]);
        time(&when);
        printf("Child process[%d] started at %s", getpid(), ctime(&when));
        
        sleep(10);
        //system("wget -o log https://sourceforge.net/projects/atom.mirror/files/latest/download");
        fp = fopen("log", "r");
        fseek(fp, -150, SEEK_END);
        while (!feof (fp) && (fscanf(fp, "%s [%d/%d]", strsearch, &fileSize, &totalFileSize) != 3))
            fgets(buf, 50, fp);
        
        (fileSize == totalFileSize) ? snprintf(string, 50, "%d Mb\n", totalFileSize/1024/1024) : snprintf(string, 7, "Error\n");
        write(fd[1], string, strlen(string));
        exit(EXIT_SUCCESS);

      default:
        close(fd[1]);
        time(&when);
        printf("Parent process[%d] started at %s", getpid(), ctime(&when));

        endID = waitpid(childID, &status, WNOHANG|WUNTRACED);
        while(endID != childID) {
           endID = waitpid(childID, &status, WNOHANG|WUNTRACED);
           switch (endID) {
              case -1: // error calling waitpid
                perror("waitpid error");
                exit(EXIT_FAILURE);
              case 0: // child still running
                time(&when);
                printf("Parent waiting for child at %s", ctime(&when));
                sleep(3);
                break;
              default:
                if (endID == childID) { //child ended
                    if (WIFEXITED(status))   printf("Child ended normally\n");
                    if (WIFSIGNALED(status)) printf("Child ended because of an uncaught signal");
                    if (WIFSTOPPED(status)) printf("Child process has stopped");
                    read(fd[0], readbuf, sizeof(readbuf));
                    printf("Received string: %s", readbuf);
                    exit(EXIT_SUCCESS);
                }
          }
        }
    }
        
    return 0;
}
