TARGETS = server_poll client

.PHONY all: $(TARGETS)

server_poll: server_poll.o
	g++ $^ -o $@
	
server_poll.o: server_poll.cpp
	g++ -c $<
	
client: client.o
	g++ $^ -o $@ -g
	
client.o: client.cpp
	g++ -c $< -g
	
.PHONY clean:
	rm -f $(TARGETS) *.o
