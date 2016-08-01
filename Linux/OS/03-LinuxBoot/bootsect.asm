
SYSSIZE equ 0x3000

SETUPLEN equ 4                 ; nr of setup-sectors
BOOTSEG  equ 0x07c0            ; original address of boot-sector
INITSEG  equ 0x9000            ; we move boot here - out of the way
SETUPSEG equ 0x9020            ; setup starts here
SYSSEG   equ 0x1000            ; system loaded at 0x10000 (65536).
ENDSEG   equ SYSSEG + SYSSIZE  ; where to stop loading

ROOT_DEV equ 0x306

org 07c00h
start:
	mov	ax, BOOTSEG ; 0x07c0
	mov	ds, ax
	mov	ax, INITSEG ; 0x9000
	mov	es, ax
	mov	cx, 256
	mov	si, 0 
	mov	di, 0
	cld ; when rep loop si+1 di+1
	rep movsw ; [ds:si] -> [es:di] ecx=ecx-1 
	
	; mov ax, cs
	; mov ds, ax
	; mov bx, address
	; mov ax, go
	; sub ax, 0x7c00
	; mov word [bx], ax         ; ip<-   
	; mov word [bx+2h], INITSEG ; cs<-
	jmp dword 0x9000:0x40 ; jmp dword [bx] ; why it doesn't work!!!
times 48-($-$$) db 0

go:	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, 0xFF00

load_setup:
	; mov dx, 0x0000 ; drive 0, head 0
	; mov cx, 0x0002 ; sector 2, track 0
	; mov bx, 0x0200 ; address=512
	; mov ax, 0x0200+SETUPLEN
	; int 0x13
	; jnc ok_load_setup
	jmp ok_load_setup
	mov dx, 0x0000
	mov ax, 0x0000
	int 0x13
	jmp load_setup

ok_load_setup:
	mov	dl, 0x00
	mov	ax, 0x0800		;AH=8 is get drive parameters
	int	0x13 ; bx=0x04(1.44M)  cx=0x4f12(max track=79, max sector=18)  dx=0x0101(max head=1, nr of soft disk=1)
	;mov	ch, 0x00
	;mov	cs:[sectors], cx
	mov	ax, INITSEG
	mov	es, ax

	mov	ah, 0x03		; read cursor pos
	xor	bh, bh
	int	0x10
	
	mov	cx, 24
	mov	bx, 0x0007		; page 0, attribute 7 (normal)
	mov	bp, msg1-0x7c00
	mov	ax, 0x1301		; write string, move cursor
	int	0x10
	
	jmp $

sectors dw 0
msg1 db 13,10
	 db "Loading system ..."
	 db 13,10,13,10
times 506-($-$$) db 0
address dw 0,0 ; used for long jump
dw 0xaa55
