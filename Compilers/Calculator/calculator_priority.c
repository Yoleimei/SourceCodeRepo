#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  BUF_SIZE  1024 * 1 // 1KB

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
int *piStack, *piStackOld;
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
			iTokenValue = *pchSrcFront - '0';
			++pchSrcFront;
			while (*pchSrcFront >= '0' && *pchSrcFront <= '9') {
				iTokenValue = iTokenValue * 10 + *pchSrcFront - '0';
				++pchSrcFront;
			}
			iToken = TOK_NUM;
			return;
		case '\n':
			iToken = TOK_LF;
			break;
		default:
			break;
		}
		++pchSrcFront;
	}
}

void match(int tk)
{
	if (iToken != tk) {
		printf("exprected token: %d, got token: %d", tk, iToken);
		exit(-1);
	}
	lex();
}

void expression(int priority)
{
	int tmp;

	if (TOK_NUM == iToken) {
		*piStack++ = iTokenValue;
		match(TOK_NUM);
	}
	else if (TOK_LBR == iToken) {
		match(TOK_LBR);
		expression(TOK_ADD);
		match(TOK_RBR);
	} else { }
	
	while (iToken >= priority) {
		if (TOK_MUL == iToken) {
			match(TOK_MUL);
			expression(TOK_MUL);
			tmp = *--piStack;
			tmp = *--piStack * tmp;
			*piStack++ = tmp;
		} else if (TOK_DIV == iToken) {
			match(TOK_DIV);
			expression(TOK_MUL);
			tmp = *--piStack;
			tmp = *--piStack / tmp;
			*piStack++ = tmp;
		} else if (TOK_ADD == iToken) {
			match(TOK_ADD);
			expression(TOK_MUL);
			tmp = *--piStack;
			tmp = *--piStack + tmp;
			*piStack++ = tmp;
		} else if (TOK_SUB == iToken) {
			match(TOK_SUB);
			expression(TOK_MUL);
			tmp = *--piStack;
			tmp = *--piStack - tmp;
			*piStack++ = tmp;
		} else {
			break;
		}
	}
}

int main()
{
	pchSrc = pchSrcFront = pchSrcRear = (char *)malloc(BUF_SIZE);
	piStack = piStackOld = (int *)malloc(BUF_SIZE);
	memset(pchSrc, 0, BUF_SIZE);
	memset(piStack, 0, BUF_SIZE);
	
	while (1) {
		if (pchSrcRear - pchSrc >= BUF_SIZE - 1) {
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
		
		lex();
		expression(TOK_ADD);
		printf("= %d\n", *--piStack);
	}
}
