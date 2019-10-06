.PHONY: all clean

all: myfifo rFIFO wFIFO

myfifo: myfifo.c
	gcc -Wall -o myfifo myfifo.c

rFIFO: readFIFO.c
	gcc -Wall -o rFIFO readFIFO.c

wFIFO: writeFIFO.c
	gcc -Wall -o wFIFO writeFIFO.c

clean:
	@rm -rf *.o myfifo rFIFO wFIFO FIFO

create:
	./myfifo

write:
	./wFIFO

read:
	./rFIFO
