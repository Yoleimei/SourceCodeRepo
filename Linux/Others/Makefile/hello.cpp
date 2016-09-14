#include <stdio.h>

#ifndef HELLO_H
#include "hello.h"
#endif

void Hello::WriteLine(char *str)
{
	printf("%s\n", str);
}
