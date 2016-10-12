#ifndef BASE_H
	#include "base.h"
#endif

int iLine;
int *piText, *piOldText;
char *pchData;
int *piStack;

void InitBase()
{
	piText = piOldText = (int *)malloc(BUF_LEN);
	pchData = (char *)malloc(BUF_LEN);
	piStack = (int *)malloc(BUF_LEN);

	memset(piText, 0, BUF_LEN);
	memset(pchData, 0, BUF_LEN);
	memset(piStack, 0, BUF_LEN);
}
