prog := calldir
prog_objs := main.o

CC := gcc
CFLAGS := -O0 -Wall
LDFLAGS :=

.PHONY: all clean

all: $(prog) procShow

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

procShow: procShow.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf *.o $(prog) procShow

run:
	./$(prog)
