#ifndef EVAL_H
#define EVAL_H

enum {
	INSTRUCTION_IMM,   // IMM <num>   : ax <- num             premiss: ax = address
	INSTRUCTION_LC ,   // LC          : ax <- *address(char)  premiss: ax = address of char
	INSTRUCTION_LI ,   // LI          : ax <- *address(int)   premiss: ax = address of int
	INSTRUCTION_SC ,   // SC          : *address <- ax(char)  premiss: stack top = address of int
	INSTRUCTION_SI ,   // SI          : *address <- ax(int)   premiss: stack top = address of int

	INSTRUCTION_PUSH,  // PUSH        : stack top <- ax

	INSTRUCTION_JMP,   // JMP <addr>  : pc <- address
	INSTRUCTION_JZ,    // JZ  <addr>  : pc <- address (if ax == 0)
	INSTRUCTION_JNZ,   // JNZ <addr>  : pc <- address (if ax != 0)

	INSTRUCTION_CALL,  // CALL <addr> : 
	INSTRUCTION_RET,   // RET         : 
}

#endif