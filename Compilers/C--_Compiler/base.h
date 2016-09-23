#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  BUF_LEN  (1024 * 1)

extern int iLine;
extern int *piText, *piOldText;
extern char *pchData;
extern int *piStack;

extern void InitBase();

#endif
