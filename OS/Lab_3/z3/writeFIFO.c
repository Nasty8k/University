#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFONAME "FIFO"
#define IMGNAME "data/i.jpg"

int main() {
    FILE *fd_img;
    int fd_fifo;
    char buf[500];
    
    if ((fd_fifo = open(FIFONAME, O_WRONLY)) == -1) {
        fprintf(stderr,"Невозможно открыть fifo\n");
        exit(1);
    }

    if ((fd_img = fopen(IMGNAME, "rb")) == NULL) {
        fprintf(stderr, "Cannot open img\n");
        exit(1);
    }
    
    printf ("Read from %s\n", IMGNAME);
    while (!feof(fd_img)) {
        fread(buf, 1, 500, fd_img);
        if (write(fd_fifo, buf, 500) != sizeof(buf)) {
            printf("Write Error");
            exit(1);
        }
    }
    close(fd_fifo);   
    printf ("Done %s in %s\n", IMGNAME, FIFONAME);
    return 0;
}
