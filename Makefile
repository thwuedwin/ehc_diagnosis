CC=gcc
CFLAGS=-Wall -O2
OBJ=main.c enhanced_hypercube.c

all:
	$(CC) $(CFLAGS) -o main $(OBJ)

clean:
	rm -f main
