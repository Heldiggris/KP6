CC = gcc
CFLAGS = -g -std=c99 -w -pipe -O3

all: print execute

print:    io.o print.o
	$(CC) $^ -o $@

execute:  io.o execute.o
	$(CC) $^ -o $@

clean:
	rm -f *.o

cleanall:
	rm -f print execute *.o

