#.section .text
.global _start
#.code16

_start:
	mov %cs, %ax
	mov %ax, %ds  # move cs to ds
	mov %ax, %es  # move cs to es
	call DispStr
loop_end:
	jmp loop_end  # jump to current position, infinite loop
	
DispStr:
	mov BootMessage, %ax
	mov %ax, %bp       # move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov $16, %cx       # length of string to be displayed
	mov $0x01301, %ax  # 10h Int: ah=13h(display string) al(display mode)
	mov $0x000c, %bx   # 
	mov $0, %dx        # dh=start raw; dl=start column
	int $0x10
	ret
	
BootMessage:     
	.ascii "Hello, OS world!"
	
	.org 0x1fe
	.word 0xaa55 
