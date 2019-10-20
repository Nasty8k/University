
.PHONY: clean run

default: libMLib.so dynamic

MLib.o: MLib.c
	gcc -fPIC -c MLib.c

libMLib.so: MLib.o
	gcc -shared MLib.o -o libMLib.so

dynamic: main.c
	gcc main.c -o dynamic -ldl
		
clean:
	rm *.o *.so dynamic

run:
	./dynamic ./libMLib.so
