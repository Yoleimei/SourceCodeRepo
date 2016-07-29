org 07c00h
sectors equ 18
bootseg equ 0x07c0
sysseg  equ 0x1000
syslen  equ 17

start:
 jmp bootseg:go
 go:
 mov ax,cs
 mov ds,ax
 mov es,ax
 mov ss,ax
 mov sp,0x400


 load_system:
 mov dx,0x0000
 mov cx,0x0002
 mov ax,sysseg
 mov es,ax
 mov bx,0x0000
 mov ax,0x200+syslen
 int 0x13
 jnc ok_load
 mov dx,0x0000
 mov ax,0x0000
 int 0x13
 jmp load_system


 ok_load:
 cli


 mov ax,cs
 mov ds,ax
 lidt [idt_48]
 lgdt [gdt_48]


 mov al,0x11
 out 0x20,al
 out 0xa0,al
 mov al,0x20
 out 0x21,al
 mov al,0x28
 out 0xa1,al
 mov al,0x04
 out 0x21,al
 mov al,0x02
 out 0xa1,al
 mov al,0x01
 out 0x21,al
 out 0xa1,al
 mov al,0xff
 out 0x21,al
 out 0xa1,al


 mov bx,sysseg
 mov ax,0x0001
 lmsw ax
 jmp 0x0008:0x0000 ;这里也可以用jmp 0x0008:dword 0x00000000
 gdt:
 dw 0,0,0,0


 dw 0x07ff
 dw 0x0000
 dw 0x9a01
 dw 0x00c0


 dw 0x07ff
 dw 0x0000
 dw 0x9201
 dw 0x00c0


 idt_48:
 dw 0
 dw 0,0


 gdt_48:
 dw 0x7ff
 dw 0x7c00+gdt,0
 msg1:
 db 13,10
 db "Loading system ..."
 db 13,10,13,10
 times 510-($-$$) db 0

dw 0xaa55
