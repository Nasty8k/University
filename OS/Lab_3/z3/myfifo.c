#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFONAME "FIFO"

int main() {

    unlink(FIFONAME);
    if ((mkfifo(FIFONAME, 0666)) == -1) {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(0);
    }
    printf("%s Создан\n", FIFONAME);
    return 0;
} 
