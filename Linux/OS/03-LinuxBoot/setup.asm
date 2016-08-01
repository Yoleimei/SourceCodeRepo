[SECTION .setup]  ; setup
	mov ax, cs
	mov ds, ax  ; move cs to ds
	mov es, ax  ; move cs to es

	mov ax, BootMessage-$$
	mov bp, ax  ; move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov cx, 16  ; length of string to be displayed
	mov ax, 01301h  ; 10h Int: ah=13h(display string) al(display mode)
	mov bx, 000ch   ; 
	mov dx, 0       ; dh=start raw; dl=start column
	int 10h
	
	jmp $
BootMessage:     db "Hello, OS world!"
times 512-($-$$) db 0
