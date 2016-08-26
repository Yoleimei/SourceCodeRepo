#include <stdio.h>
#include <stdarg.h>

#define BUF_LEN 64

char buff[BUF_LEN];

void vspf(char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	vsnprintf(buff, BUF_LEN, fmt, argptr);
	va_end(argptr);
}

int main()
{
	int iNum = 30;
	float fNum = 90.0;
	char str[4] = "abc";

	vspf("%d %f %s", iNum, fNum, str);
	printf("%s\n", buff);
}
