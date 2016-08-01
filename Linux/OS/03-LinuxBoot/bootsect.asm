
SYSSIZE equ 0x3000

SETUPLEN equ 4                 ; nr of setup-sectors
BOOTSEG  equ 0x07c0            ; original address of boot-sector
INITSEG  equ 0x9000            ; we move boot here - out of the way
SETUPSEG equ 0x9020            ; setup starts here
SYSSEG   equ 0x1000            ; system loaded at 0x10000 (65536).
ENDSEG   equ SYSSEG + SYSSIZE  ; where to stop loading

ROOT_DEV equ 0x306

org 0x7c00
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
	; mov ax, go-$$
	; mov word [bx], ax         ; ip<-   
	; mov word [bx+2h], INITSEG ; cs<-
	jmp dword INITSEG:0x40 ; jmp dword [bx] ; why it doesn't work!!!
times 48-($-$$) db 0

go:	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, 0xFF00

load_setup:
	mov dx, 0x0000 ; drive 0, head 0
	mov cx, 0x0002 ; sector 2, track 0
	mov bx, 0x0200 ; address=512
	mov ax, 0x0200+SETUPLEN
	int 0x13
	jnc ok_load_setup
	;jmp $
	; -----INT 10 display start
	mov ax, ErrorMessage-$$
	mov bp, ax  ; move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov cx, 5   ; length of string to be displayed
	mov ax, 01301h  ; 10h Int: ah=13h(display string) al(display mode)
	mov bx, 000ch   ; 
	mov dx, 0       ; dh=start raw; dl=start column
	; int 10h
	; -----INT 10 display end
	
	mov dx, 0x0000
	mov ax, 0x0000
	int 0x13
	jmp load_setup

ok_load_setup:
	; jmp 0x9020:0
	mov	dl, 0x00
	mov	ax, 0x0800		;AH=8 is get drive parameters
	int	0x13 ; bx=0x04(1.44M)  cx=0x4f12(max track=79, max sector=18)  dx=0x0101(max head=1, nr of soft disk=1)
	mov	ch, 0x00
	mov ax, INITSEG
	mov ds, ax
	mov bx, sectors-$$
	mov	[bx], cx
	mov	ax, INITSEG
	mov	es, ax

	mov	ah, 0x03		; read cursor pos
	xor	bh, bh
	int	0x10
	
	mov	cx, 24
	mov	bx, 0x0007		; page 0, attribute 7 (normal)
	mov	bp, SystemMsg-$$
	mov	ax, 0x1301		; write string, move cursor
	int	0x10
	
	jmp $
	
;	mov	ax, SYSSEG
;	mov	es, ax		; segment of 0x010000
;	call	read_it
;	call	kill_motor
;	
;	seg cs
;	mov	ax, root_dev
;	cmp	ax, 0
;	jne	root_defined
;	seg cs
;	mov	bx, sectors
;	mov	ax, 0x0208		; /dev/ps0 - 1.2Mb
;	cmp	bx, 15
;	je	root_defined
;	mov	ax, 0x021c		; /dev/PS0 - 1.44Mb
;	cmp	bx, 18
;	je	root_defined
;undef_root:
;	jmp undef_root
;root_defined:
;	seg cs
;	mov	root_dev,ax
;
;	jmp	SETUPSEG:0
;
;sread:	dw 1+SETUPLEN	; sectors read of current track
;head:	dw 0			; current head
;track:	dw 0			; current track
;	
;read_it:
;	mov ax, es
;	test ax, 0x0fff
;die:	
;	jne die			; es must be at 64kB boundary
;	xor bx, bx		; bx is starting address within segment
;rp_read:
;	mov ax, es
;	cmp ax, ENDSEG		; have we loaded all yet?
;	jb ok1_read
;	ret
;ok1_read:
;	seg cs
;	mov ax,sectors
;	sub ax,sread
;	mov cx,ax
;	shl cx,#9
;	add cx,bx
;	jnc ok2_read
;	je ok2_read
;	xor ax,ax
;	sub ax,bx
;	shr ax,#9
;ok2_read:
;	call read_track
;	mov cx,ax
;	add ax,sread
;	seg cs
;	cmp ax,sectors
;	jne ok3_read
;	mov ax,#1
;	sub ax,head
;	jne ok4_read
;	inc track
;ok4_read:
;	mov head,ax
;	xor ax,ax
;ok3_read:
;	mov sread,ax
;	shl cx,#9
;	add bx,cx
;	jnc rp_read
;	mov ax,es
;	add ax,#0x1000
;	mov es,ax
;	xor bx,bx
;	jmp rp_read
;read_track:
;	push ax
;	push bx
;	push cx
;	push dx
;	mov dx,track
;	mov cx,sread
;	inc cx
;	mov ch,dl
;	mov dx,head
;	mov dh,dl
;	mov dl,#0
;	and dx,#0x0100
;	mov ah,#2
;	int 0x13
;	jc bad_rt
;	pop dx
;	pop cx
;	pop bx
;	pop ax
;	ret
;bad_rt:	
;	mov ax,#0
;	mov dx,#0
;	int 0x13
;	pop dx
;	pop cx
;	pop bx
;	pop ax
;	jmp read_track
;	
;kill_motor:
;	push dx
;	mov dx,#0x3f2
;	mov al,#0
;	outb
;	pop dx
;	ret
	
sectors:
	dw 0
ErrorMessage:
	db 'Error'
SystemMsg:
	db 13,10
	db "Loading system ..."
	db 13,10,13,10
times 506-($-$$) db 0
address:
	dw 0,0 ; used for long jump
dw 0xaa55

%include "setup.asm"
