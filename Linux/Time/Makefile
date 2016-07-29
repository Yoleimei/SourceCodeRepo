TARGETS = time

.PHONY all: $(TARGETS)

time: time.o
	g++ $^ -o $@
	
time.o: time.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
