	.file	"hello.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello, World!"
	.text
	.globl	show
	.type	show, @function
show:
.LFB12:
	.cfi_startproc
	movl	$.LC0, %edi
	jmp	puts
	.cfi_endproc
.LFE12:
	.size	show, .-show
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	call	show
	popq	%rdx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.1-2ubuntu1~12.04) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
