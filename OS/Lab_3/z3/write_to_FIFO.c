#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "myFIFO"
#define IMG "data/i.jpg"
#define MAXBUFF 128

int main(void)
{
    int  fd, n;
    FILE *fd_img;
    char buff[MAXBUFF];
    
    if ((fd_img = fopen(IMG, "r")) == NULL) {
            printf ("Cannot open img\n");
            exit(1);
    }
    printf ("Writing %s > %s\n", IMG, FIFO);

    if ((fd = open(FIFO, O_WRONLY)) < 0 ) {
        printf("Error open\n");
        exit(1);
    }

    while ((n = fread(buff, sizeof(char), MAXBUFF, fd_img)) > 0) {
        if (write(fd, buff, n) != n) {
            printf("Error write\n");
            exit(1);
        }
    }
    close(fd);
    return 0;
}
