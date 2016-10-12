CFLAGS=-g

lexTest:
	gcc -c base.c $(CFLAGS)
	gcc -c lexical.c $(CFLAGS)
	gcc -c testLex.c $(CFLAGS)
	gcc -o lexTest base.o lexical.o testLex.o $(CFLAGS)

.PHONY clean:
	rm -rf lexTest *.o
