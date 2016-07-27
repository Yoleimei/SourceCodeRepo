TARGETS = server_epoll client

.PHONY all: $(TARGETS)

server_epoll: server_epoll.o
	g++ $^ -o $@
	
server_epoll.o: server_epoll.cpp
	g++ -c $<
	
client: client.o
	g++ $^ -o $@ -g
	
client.o: client.cpp
	g++ -c $< -g
	
.PHONY clean:
	rm -f $(TARGETS) *.o
