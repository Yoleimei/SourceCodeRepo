OBJECT = \
simple_thread \
thread_incr_mutex \
thread_product_consume_condition

.PHONY all: $(OBJECT)

simple_thread: simple_thread.o
	g++ $^ -o $@ -lpthread

thread_incr_mutex: thread_incr_mutex.o
	g++ $^ -o $@ -lpthread
	
thread_product_consume_condition: thread_product_consume_condition.o
	g++ $^ -o $@ -lpthread
	
.PHONY clean:
	rm -f $(OBJECT) *.o