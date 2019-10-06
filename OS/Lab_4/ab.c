#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void my_handler(int nsig){ 
    while(1)
    putchar('C');
}
int main(void) {

    pid_t childID;

    childID = fork();    
    switch(childID) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    
      case 0:
        while (1) {
            putchar('A');
            
        }


        exit(EXIT_SUCCESS);

      default:
        while (1) {
            putchar('B');
            signal(SIGUSR1, my_handler);            
        }

        exit(EXIT_SUCCESS);
    }
        
    return 0;
}
