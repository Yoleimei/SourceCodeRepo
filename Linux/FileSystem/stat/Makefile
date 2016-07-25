TARGETS = stat statvfs

.PHONY all: $(TARGETS)

stat: stat.o
	g++ $^ -o $@
	
stat.o: stat.cpp
	g++ -c $<
	
statvfs: statvfs.o
	g++ $^ -o $@
	
statvfs.o: statvfs.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
