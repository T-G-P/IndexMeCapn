CC = gcc
CFLAGS = -Wall -g
CFILES = tokenizer.c sorted-list.c main.c -c

all: main archive
	$(CC) sorted-list.o main.o -o index
	rm *.o

main:
	$(CC) $(CFILES) $(CFLAGS)

archive: main
	ar -r libsl.a tokenizer.o sorted-list.o
clean:
	rm -f index
	rm -f *.o
	rm -f libsl.a
