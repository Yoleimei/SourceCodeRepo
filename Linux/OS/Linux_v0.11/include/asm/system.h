#define move_to_user_mode() \
__asm__ ("movl %%esp,%%eax\n\t" \
	"pushl $0x17\n\t" \
	"pushl %%eax\n\t" \
	"pushfl\n\t" \
	"pushl $0x0f\n\t" \
	"pushl $1f\n\t" \
	"iret\n" \
	"1:\tmovl $0x17,%%eax\n\t" \
	"movw %%ax,%%ds\n\t" \
	"movw %%ax,%%es\n\t" \
	"movw %%ax,%%fs\n\t" \
	"movw %%ax,%%gs" \
	:::"ax")
/**
 * if priviledge changes from 3 to 0, CPU will push old SS and old ESP
 * the code bellow simulates this situation
 * when iret (change from 0 to 3), the old ESP and old SS will be poped
 */
// movl %esp, %eax
// pushl $0x17  # SS (Selector in LDT, DI=2, TI=1, RPL=3)
// pushl %eax   # ESP
// pushfl       # EFLAGS
// pushl $0x0f  # CS (Selector in LDT, DI=1, TI=1, RPL=3)
// pushl $1f    # EIP  # (f:forward b:backward)
// iret         # CPU will set SS:EIP and SS:ESP when iret
// 1:
// movl $0x17, %eax  # Selector=0x17: DI=2, TI=1, RPL=3 
// movw %ax, %ds     # set DS, ES, FS, GS
// movw %ax, %es
// movw %ax, %fs
// movw %ax, %gs

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)
#define nop() __asm__ ("nop"::)

#define iret() __asm__ ("iret"::)

// dpl: descriptor priviledge level
#define _set_gate(gate_addr,type,dpl,addr) \  // idt (tail of head.s)
__asm__ ("movw %%dx,%%ax\n\t" \
	"movw %0,%%dx\n\t" \
	"movl %%eax,%1\n\t" \
	"movl %%edx,%2" \
	: \
	: "i" ((short) (0x8000+(dpl<<13)+(type<<8))), \  // 0x8000 means P=1, DPL(14-13), TYPE(11-8)
	"o" (*((char *) (gate_addr))), \   // low 4 bytes of descriptor
	"o" (*(4+(char *) (gate_addr))), \ // hight 4 bytes of descriptor
	"d" ((char *) (addr)),"a" (0x00080000))
// movl $addr, %edx                       // edx=$addr
// movl $0x80000, %eax                    // eax=0x00080000
// movw %dx, %ax                          // eax=0x00080000 + (addr & 0xFFFF)
// movw $0x8000+(dpl<<13)+(type<<8), %dx  // edx=$0x8000+(dpl<<13)+(type<<8)  # set P, DPL, TYPE
// movl %eax, gate_addr                   // !!! selector=0x8(TI=0; RPL=0), offset=addr
// selector=0x8 is very important, 'cause it is Kernel Code Segment which DPL=0!!!
// movl %edx, gate_addr+4                 // P=1, DPL=dpl, TYPE=type

#define set_intr_gate(n,addr) \    // interrupt gate
	_set_gate(&idt[n],14,0,addr)  // TYPE=14=1110b (32-bit interrupt gate), DPL=0

#define set_trap_gate(n,addr) \    // trap gate
	_set_gate(&idt[n],15,0,addr)  // TYPE=15=1111b (32-bit trap gate), DPL=0

#define set_system_gate(n,addr) \  // system gate
	_set_gate(&idt[n],15,3,addr)  // TYPE=15=1111b (32-bit trap gate), DPL=3

#define _set_seg_desc(gate_addr,type,dpl,base,limit) {\
	*(gate_addr) = ((base) & 0xff000000) | \
		(((base) & 0x00ff0000)>>16) | \
		((limit) & 0xf0000) | \
		((dpl)<<13) | \
		(0x00408000) | \
		((type)<<8); \
	*((gate_addr)+1) = (((base) & 0x0000ffff)<<16) | \
		((limit) & 0x0ffff); }

#define _set_tssldt_desc(n,addr,type) \
__asm__ ("movw $104,%1\n\t" \
	"movw %%ax,%2\n\t" \
	"rorl $16,%%eax\n\t" \
	"movb %%al,%3\n\t" \
	"movb $" type ",%4\n\t" \
	"movb $0x00,%5\n\t" \
	"movb %%ah,%6\n\t" \
	"rorl $16,%%eax" \
	::"a" (addr), "m" (*(n)), "m" (*(n+2)), "m" (*(n+4)), \
	 "m" (*(n+5)), "m" (*(n+6)), "m" (*(n+7)) \
	)

#define set_tss_desc(n,addr) _set_tssldt_desc(((char *) (n)),addr,"0x89")
#define set_ldt_desc(n,addr) _set_tssldt_desc(((char *) (n)),addr,"0x82")
