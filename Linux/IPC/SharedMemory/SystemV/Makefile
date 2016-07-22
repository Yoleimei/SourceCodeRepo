TARGETS = shm_reader shm_writer shm

.PHONY all: $(TARGETS)

shm_reader: systemv_shm_reader.o binary_sems.o
	g++ $^ -o $@ 

shm_writer: systemv_shm_writer.o binary_sems.o
	g++ $^ -o $@ 

binary_sems.o: binary_sems.cpp
	g++ -c $<

shm: shm.o
	g++ $^ -o $@ 
	
shm.o: shm.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
