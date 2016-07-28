TARGETS = server client socketpair

.PHONY all: $(TARGETS)

server:
	g++ server.cpp -o server
	
client:
	g++ client.cpp -o client

socketpair:
	g++ socketpair.cpp -o socketpair
	
.PHONY clean:
	rm -f $(TARGETS) *.o
