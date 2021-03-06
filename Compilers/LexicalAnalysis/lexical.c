#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  SRC_BUF_SIZE  1024 * 1 // 1KB

enum eTok{
	TOK_NUM = 128, // [0-9]+
	TOK_ADD,       // +
	TOK_SUB,       // -
	TOK_MUL,       // *
	TOK_DIV,       // /
	TOK_LBR,       // (
	TOK_RBR,       // )
	TOK_LF         // \n
};

char *pchSrc, *pchSrcFront, *pchSrcRear;
int iToken;
int iTokenValue = 0;

void lex()
{
	while (pchSrcFront < pchSrcRear) {
		switch(*pchSrcFront) {
		case '+': iToken = TOK_ADD; ++pchSrcFront; return;
		case '-': iToken = TOK_SUB; ++pchSrcFront; return;
		case '*': iToken = TOK_MUL; ++pchSrcFront; return;
		case '/': iToken = TOK_DIV; ++pchSrcFront; return;
		case '(': iToken = TOK_LBR; ++pchSrcFront; return;
		case ')': iToken = TOK_RBR; ++pchSrcFront; return;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			iTokenValue = iTokenValue * 10 + *pchSrcFront - '0';
			if (*(pchSrcFront+1) < '0' || *(pchSrcFront+1) > '9') {
				iToken = TOK_NUM;
				++pchSrcFront;
				return;
			}
			break;
		case '\n':
			iToken = TOK_LF;
			break;
		default:
			break;
		}
		++pchSrcFront;
	}
}

int main()
{
	pchSrc = pchSrcFront = pchSrcRear = (char *)malloc(SRC_BUF_SIZE);
	
	while (1) {
		if (pchSrcRear - pchSrc >= SRC_BUF_SIZE - 1) {
			printf("src buffer full\n");
			exit(0);
		}
		char c;
		do { 
			c = getc(stdin);
			if ('\r' == c || '\n' == c) {
				*pchSrcRear++ = '\n';
				break;
			} else {
				*pchSrcRear++ = c;
			}
		} while(1);
		while (pchSrcFront < pchSrcRear) {
			lex();
			if (TOK_NUM == iToken) {
				printf("%d %d\n", iToken, iTokenValue);
				iTokenValue = 0;
			}
			else if(TOK_LF != iToken)
				printf("%d\n", iToken);
		}
	}
}
