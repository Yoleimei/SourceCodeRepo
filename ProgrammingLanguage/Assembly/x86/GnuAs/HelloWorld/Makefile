# compile .c file to .s file
sfile:
	gcc -S -Os hello.c
# compile .s file to .o file
ofile:
	as -o hello.o hello.s
# link .o file to exe file
exefile:
	gcc -o hello hello.o
clean:
	rm -f hello.s hello.o hello

