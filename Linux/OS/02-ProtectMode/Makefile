.PHONY all: protectmode.img

protectmode.img: protectmode.asm
	nasm protectmode.asm -o protectmode.img

.PHONY clean:
	rm -f bootsector *.o *.img
