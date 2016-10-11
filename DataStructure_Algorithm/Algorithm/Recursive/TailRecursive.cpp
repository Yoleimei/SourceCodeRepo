#include <stdio.h>

// return -> break;
// tailRecursive -> continue

int factorialTailRecurse(int a)
{
	if (a <= 1)
		return 1;
	
	
	return a * factorialTailRecurse(a-1);
}

int factorialLoop(int a)
{
	int ret = 1;
	
	while (true) {
		if (a <= 1)
			break;
		
		ret = a * ret;
		a = a-1;
	}
	
	return ret;
}

int main()
{
	tailRecursive(3);
	loop(3);
}
