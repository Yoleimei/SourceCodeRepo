#ifndef EVAL_H
#define EVAL_H

enum {
	INSTRUCTION_IMM,   // IMM <num>    : ax <- num             premiss: ax = address
	INSTRUCTION_LC ,   // LC           : ax <- *address(char)  premiss: ax = address of char
	INSTRUCTION_LI ,   // LI           : ax <- *address(int)   premiss: ax = address of int
	INSTRUCTION_SC ,   // SC           : *address <- ax(char)  premiss: stack top = address of int
	INSTRUCTION_SI ,   // SI           : *address <- ax(int)   premiss: stack top = address of int

	INSTRUCTION_PUSH,  // PUSH         : stack top <- ax

	INSTRUCTION_JMP,   // JMP <addr>   : pc <- address
	INSTRUCTION_JZ,    // JZ  <addr>   : pc <- address (if ax == 0)
	INSTRUCTION_JNZ,   // JNZ <addr>   : pc <- address (if ax != 0)

	INSTRUCTION_CALL,  // CALL <addr>  : push return address, jmp to callee
//	INSTRUCTION_RET,   // RET          : 
	INSTRUCTION_ENT,   // ENT <size>   : push current stack base pointer, reserve space for arguments
	INSTRUCTION_ADJ,   // ADJ <size>   : remove arguments from stack
	INSTRUCTION_LEV,   // LEV          : restore sp, bp, pc
	INSTRUCTION_LEA,   // LEA <offset> : get argument

	INSTRUCTION_OR,
	INSTRUCTION_XOR,
	INSTRUCTION_AND,
	INSTRUCTION_EQ,
	INSTRUCTION_NE,
	INSTRUCTION_LT,
	INSTRUCTION_GT,
	INSTRUCTION_LE,
	INSTRUCTION_GE,
	INSTRUCTION_SHL,
	INSTRUCTION_SHR,
	INSTRUCTION_ADD,
	INSTRUCTION_SUB,
	INSTRUCTION_MUL,
	INSTRUCTION_DIV,
	INSTRUCTION_MOD
};

extern int eval();

#endif