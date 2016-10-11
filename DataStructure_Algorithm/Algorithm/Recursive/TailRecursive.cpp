#include <stdio.h>

// return -> break;
// tailRecursive -> continue

int factorialRecurse(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * factorialRecurse(n-1);
}

//  |
// \|/

int factorialTailRecurse(int ret, int n)
{
	if (n <= 1)
		return ret;
	else
		return factorialTailRecurse(ret * n, n-1);
}

int factorialTailRecurseAux(int n)
{
	int ret = 1;
	ret = factorialTailRecurse(ret, n);
	return ret;
}

int factorialLoop(int n)
{
	int ret = 1;

	while (n > 1) {
		ret = ret * n;
		n--;
	}

	return ret;
}

int main()
{
	printf("%d\n", factorialTailRecurseAux(3));
	printf("%d\n", factorialLoop(3));
}
