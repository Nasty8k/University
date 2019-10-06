#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFONAME "FIFO"
#define IMGNAME "img.jpg"

int main() {
    int fd_fifo;
    FILE *fd_img;
    char buf[500];

    if ((fd_fifo = open(FIFONAME, O_RDONLY)) < 0) {
        printf("Невозможно открыть fifo\n");
        exit(1);
    }

    if (read(fd_fifo, &buf, sizeof(buf)) == -1) {
        printf("Невозможно прочесть из FIFO\n");
        exit(1);
    } else {

        if ((fd_img = fopen(IMGNAME, "wb")) == NULL) {
            printf ("Cannot open img\n");
            exit(1);
        }
        printf ("Write this img\n");
        do {
              if(fwrite(buf, 1, 500, fd_img) != sizeof(buf)) {
                  printf("Write Error");
                  exit(1);
              }
        } while (read(fd_fifo, &buf, sizeof(buf)) > 0);
        printf ("Done %s\n", IMGNAME);
        close(fd_fifo);
    }
    return 0;
} 
