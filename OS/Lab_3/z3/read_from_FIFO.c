#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "myFIFO"
#define NEWIMG "newImg.jpg"
#define MAXBUFF 128

int main(void)
{
    int  fd, n;
    FILE *fd_NEW_img;
    char buff[MAXBUFF];

    if (mknod(FIFO, S_IFIFO | 0666, 0) < 0) {
        printf("Error mknod FIFO\n");
        exit(1);
    }

    if ((fd = open(FIFO, O_RDONLY)) < 0 ) {
        printf("Error open\n");
        exit(1);
    }

    if ((fd_NEW_img = fopen(NEWIMG, "w")) == NULL) {
            printf ("Cannot open img\n");
            exit(1);
    }
    printf("[%s] was created\n", NEWIMG);
    
    while ((n = read(fd, buff, MAXBUFF)) > 0) {
        if (fwrite(buff, sizeof(char), n, fd_NEW_img) != n) {
            printf("Error write\n");
            exit(1);
        }
    }
    printf("Done!\n");
    close(fd);
    if (unlink(FIFO) < 0) {
        printf("Error unlink(FIFO)\n");
        exit(1);
    }

    return 0;
}
