#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

static void f1()
{
	longjmp(env, 1);
}

static void f2()
{
	longjmp(env, 2);
}

int main()
{
	int i;
	i = setjmp(env);
	switch (i) {
	case 0:
		printf("0\n");
		f1();
		break;
	case 1:
		printf("1\n");
		f2();
	case 2:
		printf("2\n");
		break;
	default:
		printf("default\n");
		break;
	}
}