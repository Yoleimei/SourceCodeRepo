TARGETS = simple_signal

.PHONY all: $(TARGETS)

simple_signal: simple_signal.o
	g++ $^ -o $@
	
simple_signal.o: simple_signal.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
