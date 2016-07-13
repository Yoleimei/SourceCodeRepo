.PHONY all: dir

dir: dir.o
	g++ $^ -o $@
	
dir.o: dir.cpp

.PHONY clean:
	rm -f dir *.o
