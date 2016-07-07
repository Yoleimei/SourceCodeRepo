.PHONY all: shm_reader shm_writer

shm_reader: systemv_shm_reader.o binary_sems.o
	g++ $^ -o $@ 

shm_writer: systemv_shm_writer.o binary_sems.o
	g++ $^ -o $@ 

binary_sems.o: binary_sems.h

.PHONY clean:
	rm -f shm_reader shm_writer *.o
