.global _start
.code16

SYSSIZE = 0x3000

SETUPLEN = 4                 # nr of setup-sectors
BOOTSEG  = 0x07c0            # original address of boot-sector
INITSEG  = 0x9000            # we move boot here - out of the way
SETUPSEG = 0x9020            # setup starts here
SYSSEG   = 0x1000            # system loaded at 0x10000 (65536).
ENDSEG   = SYSSEG + SYSSIZE  # where to stop loading

ROOT_DEV = 0x306

_start:
	mov	$BOOTSEG, %ax # 0x07c0
	mov	%ax, %ds
	mov	$INITSEG, %ax # 0x9000
	mov	%ax, %es
	mov	$256, %cx
	mov	$0, %si
	mov	$0, %di
	cld # when rep loop si+1 di+1
	rep movsw # [ds:si] -> [es:di] ecx=ecx-1 
	
	# mov ax, cs
	# mov ds, ax
	# mov bx, address
	# mov ax, go-$$
	# mov word [bx], ax         # ip<-   
	# mov word [bx+2h], INITSEG # cs<-
	ljmp $INITSEG, $go # jump dword [bx] # why it doesn't work!!!

#.org 0x30
go:	mov	%cs, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %ss
	mov	$0xFF00, %sp

load_setup:
	# mov $0x0000, %dx # drive 0, head 0
	# mov $0x0002, %cx # sector 2, track 0
	# mov $0x0200, %bx # address=512
	# mov $0x0200+$SETUPLEN, %ax
	# int $0x13
	# jnc ok_load_setup
	jmp ok_load_setup
	# -----INT 10 display start
	mov ErrorMessage, %ax
	mov %ax, %bp      # move BootMessage's address to bp, [ES:BP] indicates the address of the string
	mov $5, %cx       # length of string to be displayed
	mov $0x01301, %ax  # 10h Int: ah=13h(display string) al(display mode)
	mov $0x000c, %bx   # 
	mov $0, %dx       # dh=start raw# dl=start column
	# int $10h
	# -----INT 10 display end
	
	mov $0, %dx
	mov $0, %ax
	int $0x13
	jmp load_setup

ok_load_setup:
	# jump 0x9020:0
	mov	$0, %dl
	mov	$0x0800, %ax		#AH=8 is get drive parameters
	int	$0x13 # bx=0x04(1.44M)  cx=0x4f12(max track=79, max sector=18)  dx=0x0101(max head=1, nr of soft disk=1)
	mov	$0, %ch
	mov $INITSEG, %ax
	mov %ax, %ds
	mov sectors, %ebx
	movw %cx, (%ebx)
	mov	$INITSEG, %ax
	mov	%ax, %es

	mov	$0x03, %ah		# read cursor pos
	xor	%bh, %bh
	int	$0x10
	
	mov	$24, %cx
	mov	$0x0007, %bx		# page 0, attribute 7 (normal)
	mov	SystemMsg, %bp
	mov	$0x1301, %ax		# write string, move cursor
	int	$0x10
	
	jmp .
	
#	mov	ax, SYSSEG
#	mov	es, ax		# segment of 0x010000
#	call	read_it
#	call	kill_motor
#	
#	seg cs
#	mov	ax, root_dev
#	cmp	ax, 0
#	jne	root_defined
#	seg cs
#	mov	bx, sectors
#	mov	ax, 0x0208		# /dev/ps0 - 1.2Mb
#	cmp	bx, 15
#	je	root_defined
#	mov	ax, 0x021c		# /dev/PS0 - 1.44Mb
#	cmp	bx, 18
#	je	root_defined
#undef_root:
#	jump undef_root
#root_defined:
#	seg cs
#	mov	root_dev,ax
#
#	jump	SETUPSEG:0
#
#sread:	dw 1+SETUPLEN	# sectors read of current track
#head:	dw 0			# current head
#track:	dw 0			# current track
#	
#read_it:
#	mov ax, es
#	test ax, 0x0fff
#die:	
#	jne die			# es must be at 64kB boundary
#	xor bx, bx		# bx is starting address within segment
#rp_read:
#	mov ax, es
#	cmp ax, ENDSEG		# have we loaded all yet?
#	jb ok1_read
#	ret
#ok1_read:
#	seg cs
#	mov ax,sectors
#	sub ax,sread
#	mov cx,ax
#	shl cx,#9
#	add cx,bx
#	jnc ok2_read
#	je ok2_read
#	xor ax,ax
#	sub ax,bx
#	shr ax,#9
#ok2_read:
#	call read_track
#	mov cx,ax
#	add ax,sread
#	seg cs
#	cmp ax,sectors
#	jne ok3_read
#	mov ax,#1
#	sub ax,head
#	jne ok4_read
#	inc track
#ok4_read:
#	mov head,ax
#	xor ax,ax
#ok3_read:
#	mov sread,ax
#	shl cx,#9
#	add bx,cx
#	jnc rp_read
#	mov ax,es
#	add ax,#0x1000
#	mov es,ax
#	xor bx,bx
#	jump rp_read
#read_track:
#	push ax
#	push bx
#	push cx
#	push dx
#	mov dx,track
#	mov cx,sread
#	inc cx
#	mov ch,dl
#	mov dx,head
#	mov dh,dl
#	mov dl,#0
#	and dx,#0x0100
#	mov ah,#2
#	int 0x13
#	jc bad_rt
#	pop dx
#	pop cx
#	pop bx
#	pop ax
#	ret
#bad_rt:	
#	mov ax,#0
#	mov dx,#0
#	int 0x13
#	pop dx
#	pop cx
#	pop bx
#	pop ax
#	jump read_track
#	
#kill_motor:
#	push dx
#	mov dx,#0x3f2
#	mov al,#0
#	outb
#	pop dx
#	ret
	
sectors:
	.word 0
ErrorMessage:
	.ascii "Error"
SystemMsg:
	.byte 13,10
	.ascii "Loading system ..."
	.byte 13,10,13,10
.org 0x1fa
address:
	.word 0,0 # used for long jump
.word 0xaa55

#%include "setup.asm"
