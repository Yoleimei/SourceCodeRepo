.PHONY all: test

test: test.o
	g++ $^ -o $@
	
test.o: test.cpp

.PHONY clean:
	rm -f test *.o
	
