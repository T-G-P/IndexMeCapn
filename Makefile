CFLAGS = -Wall -g

all: index

index: tokenizer.o dirtest.o hashadd.o
	gcc $(CFLAGS) tokenizer.o dirtest.o hashadd.o -o index

tokenizer.o: tokenizer.c
	gcc $(CFLAGS) -c tokenizer.c -o tokenizer.o

dirtest.o: dirtest.c
	gcc $(CFLAGS) -c dirtest.c -o dirtest.o

hashadd.o: hashadd.c
	gcc $(CFLAGS) -c hashadd.c -o hashadd.o

clean:
	rm -f index
	rm -f *.o
