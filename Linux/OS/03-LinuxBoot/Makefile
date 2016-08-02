.PHONY all: bootsect.img

bootsect.o: bootsect.s
	as -o $@ $^

bootsect: bootsect.o
	ld --oformat binary -N -Ttext 0x7c00 -o $@ $^
	# --oformat=output-format
	# -N=--omagic: set the text and data sections to be readable and writeable
	# -Tbss=org / -Tdata=org / -Ttext=org : locate a section in the output file at the absolute address given by org
	
bootsect.img: bootsect
	dd if=bootsect of=bootsect.img bs=512 count=1
	# if=input-file
	# of=ouput-file
	# bs=<BYTES> : read and write <BYTES> bytes at a time
	# count=<BLOCKS> : copy only <BLOCKS> input blocks

.PHONY clean:
	rm -f bootsect *.o *.img
