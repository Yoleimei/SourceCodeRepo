	.file	"hello.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello, World!"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	movl	$.LC0, %edi
	jmp	puts
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.1-2ubuntu1~12.04) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
