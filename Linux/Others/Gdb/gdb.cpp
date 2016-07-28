#include <stdio.h>

int add(const int &a, const int &b)
{
	int iRet = a + b;
	return iRet;
}

int main()
{
	int a = 3;
	int b = 4;
	int c = add(a, b);
	printf("3 + 4 = %d", c);
	
	return 0;
}
