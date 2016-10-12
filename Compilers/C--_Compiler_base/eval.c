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
		else if (INSTRUCTION_LEA == op)  { ax = (int)(bp + *pc++); }
		
		else if (INSTRUCTION_OR == op) { ax = *sp++ | ax; }
		else if (INSTRUCTION_XOR == op) { ax = *sp++ ^ ax; }
		else if (INSTRUCTION_AND == op) { ax = *sp++ & ax; }
		else if (INSTRUCTION_EQ == op) { ax = *sp++ == ax; }
		else if (INSTRUCTION_NE == op) { ax = *sp++ != ax; }
		else if (INSTRUCTION_LT == op) { ax = *sp++ < ax; }
		else if (INSTRUCTION_LE == op) { ax = *sp++ <= ax; }
		else if (INSTRUCTION_GT == op) { ax = *sp++ > ax; }
		else if (INSTRUCTION_GE == op) { ax = *sp++ >= ax; }
		else if (INSTRUCTION_SHL == op) { ax = *sp++ << ax; }
		else if (INSTRUCTION_SHR == op) { ax = *sp++ >> ax; }
		else if (INSTRUCTION_ADD == op) { ax = *sp++ + ax; }
		else if (INSTRUCTION_SUB == op) { ax = *sp++ - ax; }
		else if (INSTRUCTION_MUL == op) { ax = *sp++ * ax; }
		else if (INSTRUCTION_DIV == op) { ax = *sp++ / ax; }
		else if (INSTRUCTION_MOD == op) { ax = *sp++ % ax; }
		else {
			printf("unknown instruction: %d\n", op);
			return -1;
		}
	}
	return 0;
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