CC = gcc
CFLAGS = -g -std=c99 -w -pipe -O3

all: execute

print:    io.o
	$(CC) $^ -o $@

execute:  io.o execute.o
	$(CC) $^ -o $@

clean:
	rm -f *.o

cleanall:
	rm -f execute *.o

