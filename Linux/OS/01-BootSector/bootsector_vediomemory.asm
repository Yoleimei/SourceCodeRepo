;nasm boot.asm -o boot.img
	org 07c00h  ; tell the compiler to load from 7c00h
	mov ax, cs
	mov ds, ax  ; move cs to ds
	mov es, ax  ; move cs to es
	call DispStr
	jmp $  ; jump to current position, infinite loop
DispStr:
	mov ax, 0b800h
	mov es, ax
	mov di, 0
	
	mov ah, 0ch
	mov al, 'P'
	mov [es:di], ax
	ret
	
times 510-($-$$) db 0
dw 0xaa55 
