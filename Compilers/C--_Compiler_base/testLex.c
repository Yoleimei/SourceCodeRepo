#include "base.h"
#include "lexical.h"

int main()
{
	InitBase();
	InitLex();

	while (1) {
		char c;
		do { 
			c = getc(stdin);
			if ('\r' == c || '\n' == c) {
				*pchOldSrc++ = '\n';
				break;
			} else {
				*pchOldSrc++ = c;
			}
		} while(1);
		
		while (pchSrc < pchOldSrc) {
			lex();
			if (0 != iToken) {
				if (TOK_NUM == iToken)
					printf("= %d %d\n", iToken, iTokenValue);
				else if (TOK_ID == iToken) {
					printf("= %d %p\n", iToken, stCurrentId[Name]);
				}
				else
					printf("= %d\n", iToken);
			}
		}
	}
}
