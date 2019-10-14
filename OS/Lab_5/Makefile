CC = gcc
CFLAGS = -rdynamic

.PHONY: clean run

default: dynamic

dynamic: main.c
	$(CC) $(CFLAGS) -o dynamic main.c -ldl

clean:
	rm dynamic

run:
	./dynamic

libm:
	./dynamic /lib64/libm.so.6	 
