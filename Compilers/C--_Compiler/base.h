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
extern int ax, *pc, *bp, *sp;
extern int *idmain;

extern void InitBase();

#endif
