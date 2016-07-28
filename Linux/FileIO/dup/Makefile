TARGETS = ylm_dup

.PHONY all: $(TARGETS)

ylm_dup: ylm_dup.o
	g++ $^ -o $@
	
ylm_dup.o: ylm_dup.cpp
	g++ -c $<
	
.PHONY clean:
	rm -f $(TARGETS) *.o
