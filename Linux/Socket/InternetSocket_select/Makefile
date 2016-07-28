TARGETS = server_select client

.PHONY all: $(TARGETS)

server_select: server_select.o
	g++ $^ -o $@
	
server_select.o: server_select.cpp
	g++ -c $<
	
client: client.o
	g++ $^ -o $@ -g
	
client.o: client.cpp
	g++ -c $< -g
	
.PHONY clean:
	rm -f $(TARGETS) *.o
