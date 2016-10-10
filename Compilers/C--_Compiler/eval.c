#ifndef EVAL_H
	#include "eval.h"
#endif

int eval()
{
	int op, *tmp;
	while (1) {
		op = *pc++;
		if (INSTRUCTION_IMM == op)       { ax = *pc++; }
		else if (INSTRUCTION_LC == op)   { ax = *(char *)ax; }
		else if (INSTRUCTION_LI == op)   { ax = *(int *)ax; }
		else if (INSTRUCTION_SC == op)   { *(char *)*sp++ = ax; }
		else if (INSTRUCTION_SI == op)   { *(int *)*sp++ = ax; }
		else if (INSTRUCTION_PUSH == op) { *--sp = ax; }
		else if (INSTRUCTION_JMP == op)  { pc = (int *)*pc; }
		else if (INSTRUCTION_JZ == op)   { ax ? (pc + 1) : (int *)*pc; }
		else if (INSTRUCTION_JNZ == op)  { ax ? (int *)*pc : (pc + 1); }
		else if (INSTRUCTION_CALL == op) { *--sp = (int)(pc + 1); pc = (int *)*pc; }
		else if (INSTRUCTION_ENT == op)  { *--sp = (int)bp; bp = sp; sp = sp - *pc++; }
		else if (INSTRUCTION_ADJ == op)  { sp = sp + *pc++; }
		else if (INSTRUCTION_LEV == op)  { sp = bp; bp = (int *)*sp++; pc = (int *)sp++; }
		else if (INSTRUCTION_LEV == op)  { ax = (int)(bp + *pc++); }
	}
}

/*
type foo(arg1, arg2);
|       ...       |
+-----------------+
| arg2            |
+-----------------+
| arg1            |
+-----------------+
| return address  |
+-----------------+
| old bp          |
+-----------------+
| local var1      |
+-----------------+
| local var2      |
+-----------------+
|       ...       |
*/