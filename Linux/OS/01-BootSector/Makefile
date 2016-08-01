.PHONY all: bootsector.img

bootsector.o: bootsector.s
	as -o $@ $<

bootsector: bootsector.o
	ld --oformat binary -N -Ttext 0x7c00 -o $@ $<
	
bootsector.img: bootsector
	dd if=bootsector of=bootsector.img bs=512 count=1

.PHONY clean:
	rm -f bootsector *.o *.img
