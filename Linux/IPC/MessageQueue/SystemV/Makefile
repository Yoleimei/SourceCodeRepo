all: sender receiver

sender: systemv_msg_send.o
	g++ $^ -o $@
	
receiver: systemv_msg_recv.o
	g++ $^ -o $@
	
.PHONY clean:
	rm -f sender receiver *.o
