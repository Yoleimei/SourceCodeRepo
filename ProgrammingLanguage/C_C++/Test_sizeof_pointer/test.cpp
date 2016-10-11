#include <stdio.h>

int main()
{
	char * pchBuff = new char[100];
	printf("sizeof(pchBuff) = %d\n", sizeof(pchBuff));
	delete [] pchBuff;
}
