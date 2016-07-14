.PHONY all: inotify

inotify: inotify.o
	g++ $^ -o $@
	
inotify.o: inotify.cpp

.PHONY clean:
	rm -f inotify *.o
