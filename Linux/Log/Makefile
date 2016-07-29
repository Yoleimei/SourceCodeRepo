TARGETS = syslog

.PHONY all: $(TARGETS)

syslog: syslog.o
	g++ $^ -o $@
	
syslog.o: syslog.cpp
	g++ -c $<
	
.PHONY clean:
	rm $(TARGETS) *.o
