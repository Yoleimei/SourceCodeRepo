;nasm protectmode.asm -o protectmode.img
%include "protectmode.inc"

[SECTION .boot]  ; boot sector
org 07c00h       ; tell the compiler to load from 7c00h
	mov ax, cs
	mov es, ax
	mov dx, 0x0000 ; drive 0, head 0
	mov cx, 0x0002 ; sector 2, track 0
	mov bx, 0x7e00 ; address=512
	mov ax, 0x0200+3
	int 0x13
	jnc go
	
	; -----INT 10 display start
	mov ax, TestMessage
	mov bp, ax  ; move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov cx, 16  ; length of string to be displayed
	mov ax, 01301h  ; 10h Int: ah=13h(display string) al(display mode)
	mov bx, 000ch   ; 
	mov dx, 0       ; dh=start raw; dl=start column
	int 10h
	jmp $
	; -----INT 10 display end
	
go:
	jmp dword 0x0000:8000h
TestMessage db 'failed'
times 510-($-$$) db 0
dw 0xaa55
	
[SECTION .gdt]  ; global descriptor table (Descriptor = 8 bytes)
;                               Base(dd) Limit(dd-low 20 bits available) Attr(dw-lower 4 bits of higher byte are always 0)
LABEL_GDT:          Descriptor  0,       0,                              0            ; 
LABEL_DESC_CODE32:  Descriptor  0,       SegCode32Len-1,                 DA_C + DA_32 ; 
LABEL_DESC_VIDEO:   Descriptor  0B8000h, 0ffffh,                         DA_DRW       ; 

GdtLen  equ  $-LABEL_GDT  ; = 0x17; Length of gdt
GdtPtr  dw   GdtLen-1     ; Limit of gdt
        dd   0            ; Base of gdt, assigned later
times 512-($-$$) db 0
		
SelectorCode32  equ  LABEL_DESC_CODE32 - LABEL_GDT  ; = 0x08; index or offset of LABEL_DESC_CODE32
SelectorVideo   equ  LABEL_DESC_VIDEO  - LABEL_GDT  ; = 0x10; index or offset of LABEL_DESC_VIDEO

[SECTION .s16]  ; 16-bit code section in real mode
[BITS 16]
LABEL_BEGIN:
	mov ax, cs
	mov ds, ax  ; move cs to ds
	mov es, ax  ; move cs to es
	mov ss, ax  ; move cs to ss
	mov sp, 0100h  
	
	xor eax, eax  
	mov ax, cs
	shl eax, 4
	add eax, LABEL_SEG_CODE32  ; eax = LABEL_SEG_CODE32's address
	mov word [LABEL_DESC_CODE32 + 2], ax  ; 15-0 of Base
	shr eax, 16
	mov byte [LABEL_DESC_CODE32 + 4], al  ; 23-16 of Base
	mov byte [LABEL_DESC_CODE32 + 7], ah  ; 31-24 of Base
	
	xor eax, eax
	mov ax, ds
	shl eax, 4
	add eax, LABEL_GDT  ; eax = LABEL_GDT's address
	mov dword [GdtPtr + 2], eax  ; assign Base of gdt
	
	lgdt [GdtPtr]  ; load gdt to GDTR[32 bits of Base + 16 bits of Limit]
	
	cli ; Clear Interrupt
	
	; open address line A20, so that cpu can access all of the memory
	in al, 92h
	or al, 00000010b
	out 92h, al
	
	mov eax, cr0  ; control register 0
	or eax, 1  ; set PE(Paging Enable) to 1
	mov cr0, eax
	
	jmp dword SelectorCode32:0  ; congratulations
times 512-($-$$) db 0
	
[SECTION .s32]  ; 32-bit code section in protect mode
[BITS 32]
LABEL_SEG_CODE32:
	mov ax, SelectorVideo
	mov gs, ax  ; gs = 0x10 = 0001 0000
	
	mov edi, (80 * 10 + 0) * 2 ; raw=10, column=0
	mov ah, 0ch  ; 0000-black background  1100-read foreground
	mov al, 'P'
	mov [gs:edi], ax
	
	jmp $
SegCode32Len  equ  $ - LABEL_SEG_CODE32

times 512-($-$$) db 0
