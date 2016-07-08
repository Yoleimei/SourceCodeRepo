.PHONY all: sender receiver

sender: posix_msg_send.o
	g++ $^ -o $@ -lrt
	
receiver: posix_msg_recv.o
	g++ $^ -o $@ -lrt
	
.PHONY clean:
	rm -f sender receiver *.o