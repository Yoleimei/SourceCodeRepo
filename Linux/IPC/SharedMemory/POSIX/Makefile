TARGETS = shm shm_nosem shm_sem

.PHONY all: $(TARGETS)

shm: shm.o
	g++ $^ -o $@ -lrt
shm_nosem: shm_nosem.o
	g++ $^ -o $@ -lrt
shm_sem: shm_sem.o
	g++ $^ -o $@ -lrt
	
shm.o: shm.cpp
	g++ -c $<
shm_nosem.o: shm_nosem.cpp
	g++ -c $<
shm_sem.o: shm_sem.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
