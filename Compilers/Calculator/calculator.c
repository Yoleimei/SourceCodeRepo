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

void match(int tk)
{
	if (iToken != tk) {
		printf("exprected token: %d, got token: %d", tk, iToken);
		exit(-1);
	}
	iTokenValue = 0;
	lex();
}

int expr();

int term()
{
	int value = 0;
	if (TOK_LBR == iToken) {
		match(TOK_LBR);
		value = expr();
		match(TOK_RBR);
	} else {
		value = iTokenValue;
		match(TOK_NUM);
	}
	return value;
}

int factor_tail(int lvalue)
{
	if (TOK_MUL == iToken) {
		match(TOK_MUL);
		int value = lvalue * term();
		return factor_tail(value);
	} else if (TOK_DIV == iToken) {
		match(TOK_DIV);
		int value = lvalue / term();
		return factor_tail(value);
	} else {
		return lvalue;
	}
}

int factor()
{
	int lvalue = term();
	return factor_tail(lvalue);
}

int expr_tail(int lvalue)
{
	if (TOK_ADD == iToken) {
		match(TOK_ADD);
		int value = lvalue + factor();
		return expr_tail(value);
	} else if (TOK_SUB == iToken) {
		match(TOK_SUB);
		int value = lvalue - factor();
		return expr_tail(value);
	} else {
		return lvalue;
	}
}

int expr()
{
	int lvalue = factor();
	return expr_tail(lvalue);
}

int main()
{
	pchSrc = pchSrcFront = pchSrcRear = (char *)malloc(SRC_BUF_SIZE);
	memset(pchSrc, 0, SRC_BUF_SIZE);
	
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
		
		lex();
		printf("= %d\n", expr());
	}
}
