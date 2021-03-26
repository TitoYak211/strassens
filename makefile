CC=clang
CFLAGS=-c -Wall -g

all: strassens

strassens: strassens.o
	$(CC) strassens.o -o strassens

strassens.o: strassens.c
	$(CC) $(CFLAGS) strassens.c

clean:
	rm *.o strassens