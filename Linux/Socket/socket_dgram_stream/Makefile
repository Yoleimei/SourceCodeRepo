TARGETS = recv_dgram send_dgram recv_stream send_stream

.PHONY all: $(TARGETS)

recv_dgram:
	g++ recv_dgram.cpp -o recv_dgram -lpthread
	
send_dgram:
	g++ send_dgram.cpp -o send_dgram

recv_stream:
	g++ recv_stream.cpp -o recv_stream -lpthread
	
send_stream:
	g++ send_stream.cpp -o send_stream
	
.PHONY clean:
	rm -f $(TARGETS) *.o
