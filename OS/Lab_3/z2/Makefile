prog := pipework
prog_objs := pipe.o

CC := gcc
CFLAGS := -O0 -Wall
LDFLAGS :=

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf *.o $(prog)

run:
	./$(prog)
