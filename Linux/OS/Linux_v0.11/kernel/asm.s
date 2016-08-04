/*
 *  linux/kernel/asm.s
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 * asm.s contains the low-level code for most hardware faults.
 * page_exception is handled by the mm, so that isn't here. This
 * file also handles (hopefully) fpu-exceptions due to TS-bit, as
 * the fpu must be properly saved/resored. This hasn't been tested.
 */

.globl _divide_error,_debug,_nmi,_int3,_overflow,_bounds,_invalid_op
.globl _double_fault,_coprocessor_segment_overrun
.globl _invalid_TSS,_segment_not_present,_stack_segment
.globl _general_protection,_coprocessor_error,_irq13,_reserved

_divide_error:
	pushl $_do_divide_error  # 0 (assume this is stack top)
no_error_code:
	xchgl %eax,(%esp)        # exchange %eax with (%esp) which is $_do_divide_error
	pushl %ebx               # 4
	pushl %ecx               # 8
	pushl %edx               # 12
	pushl %edi               # 16
	pushl %esi               # 20
	pushl %ebp               # 24
	push %ds                 # 28
	push %es                 # 32
	push %fs                 # 36
	pushl $0		 # 40  # "error code"
	lea 44(%esp),%edx
	pushl %edx               # address of stack top
	movl $0x10,%edx          # DATA SEG in gdt
	mov %dx,%ds
	mov %dx,%es
	mov %dx,%fs
	call *%eax               # call _do_divide_error
	addl $8,%esp  # ignore (error code) and (address of stack top) that are params of _do_divide_error
	pop %fs
	pop %es
	pop %ds
	popl %ebp
	popl %esi
	popl %edi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret                    # return to 

_debug:
	pushl $_do_int3		# _do_debug
	jmp no_error_code

_nmi:
	pushl $_do_nmi
	jmp no_error_code

_int3:
	pushl $_do_int3
	jmp no_error_code

_overflow:
	pushl $_do_overflow
	jmp no_error_code

_bounds:
	pushl $_do_bounds
	jmp no_error_code

_invalid_op:
	pushl $_do_invalid_op
	jmp no_error_code

_coprocessor_segment_overrun:
	pushl $_do_coprocessor_segment_overrun
	jmp no_error_code

_reserved:
	pushl $_do_reserved
	jmp no_error_code

_irq13:
	pushl %eax
	xorb %al,%al
	outb %al,$0xF0
	movb $0x20,%al
	outb %al,$0x20
	jmp 1f
1:	jmp 1f
1:	outb %al,$0xA0
	popl %eax
	jmp _coprocessor_error

_double_fault:
	pushl $_do_double_fault
error_code:
	xchgl %eax,4(%esp)		# error code <-> %eax
	xchgl %ebx,(%esp)		# &function <-> %ebx
	pushl %ecx
	pushl %edx
	pushl %edi
	pushl %esi
	pushl %ebp
	push %ds
	push %es
	push %fs
	pushl %eax			# error code
	lea 44(%esp),%eax		# offset
	pushl %eax
	movl $0x10,%eax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	call *%ebx
	addl $8,%esp
	pop %fs
	pop %es
	pop %ds
	popl %ebp
	popl %esi
	popl %edi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret

_invalid_TSS:
	pushl $_do_invalid_TSS
	jmp error_code

_segment_not_present:
	pushl $_do_segment_not_present
	jmp error_code

_stack_segment:
	pushl $_do_stack_segment
	jmp error_code

_general_protection:
	pushl $_do_general_protection
	jmp error_code

