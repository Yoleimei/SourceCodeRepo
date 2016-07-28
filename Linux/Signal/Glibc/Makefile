TARGETS = simple_signal  sigprocmask

.PHONY all: $(TARGETS)

simple_signal: simple_signal.o
	g++ $^ -o $@
	
simple_signal.o: simple_signal.cpp
	g++ -c $<
	
sigprocmask: sigprocmask.o
	g++ $^ -o $@
	
sigprocmask.o: sigprocmask.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
