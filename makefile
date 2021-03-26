CC=clang
CFLAGS=-c -Wall -g

all: strassen

strassen: strassens.o
	$(CC) strassens.o -o strassen

strassens.o: strassens.c
	$(CC) $(CFLAGS) strassens.c

clean:
	rm *.o strassen