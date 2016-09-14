.PHONY all: test

test: main.o hello.o
	g++ $^ -o $@
	
hello.o: hello.cpp
	g++ -c $<
	
.PHONY clean:
	rm -rf test *.o
