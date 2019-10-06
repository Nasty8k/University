CC = gcc
CFLAGS = -Wall -Werror -std=c99

.PHONY: clean run

default: main read_from_FIFO write_to_FIFO

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c
	$(CC) -c main.c -o main.o

write_to_FIFO.o: write_to_FIFO.c
	$(CC) -c write_to_FIFO.c -o write_to_FIFO.o

read_from_FIFO.o: read_from_FIFO.c
	$(CC) -c read_from_FIFO.c -o read_from_FIFO.o
		
clean:
	rm *.o read_from_FIFO write_to_FIFO main newImg.jpg

run:
	./main
