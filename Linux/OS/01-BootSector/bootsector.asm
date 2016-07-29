;nasm boot.asm -o boot.img
	org 07c00h  ; tell the compiler to load from 7c00h
	mov ax, cs
	mov ds, ax  ; move cs to ds
	mov es, ax  ; move cs to es
	call DispStr
	jmp $  ; jump to current position, infinite loop
DispStr:
	mov ax, BootMessage
	mov bp, ax  ; move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov cx, 16  ; length of string to be displayed
	mov ax, 01301h  ; 10h Int: ah=13h(display string) al(display mode)
	mov bx, 000ch   ; 
	mov dx, 0       ; dh=start raw; dl=start column
	int 10h
	ret
BootMessage:     db "Hello, OS world!"
times 510-($-$$) db 0

dw 0xaa55 
