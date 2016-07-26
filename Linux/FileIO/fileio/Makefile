TARGETS = fileio

.PHONY all: $(TARGETS)

fileio: fileio.o
	g++ $^ -o $@
	
fileio.o: fileio.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
