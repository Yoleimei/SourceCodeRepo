#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  SRC_BUF_SIZE      1024 * 1 // 1KB
#define  GET_SRC_POINT(p)  ( (p - pchSrc) >= SRC_BUF_SIZE ? (p - SRC_BUF_SIZE) : p)

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

struct ast {
	int nodetype;
	struct ast *l;
	struct ast *r;
};

struct ast * newast(int nodetype, struct ast *l, struct ast *r)
{
	struct ast *a = malloc(sizeof(struct ast));
	
	if (!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	return a;
}

struct numval {
	int nodetype;
	int number;
};

struct ast *newnum(int d)
{
	struct numval *a = malloc(sizeof(struct numval));
	
	if (!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = TOK_NUM;
	a->number = d;
	return (struct ast *)a;
}

void treefree(struct ast *a)
{
	switch (a->nodetype) {
	case TOK_ADD:
	case TOK_SUB:
	case TOK_MUL:
	case TOK_DIV:
		treefree(a->r);
		treefree(a->l);
		break;
	case TOK_NUM:
		break;
	default:
		printf("internal error: free bad node %c\n", a->nodetype);
	}
	free(a);
}

int eval(struct ast *a)
{
	int v;
	
	if (!a) {
		printf("internal error, null eval");
		return 0;
	}
	
	switch(a->nodetype) {
	case TOK_NUM: v = ((struct numval *)a)->number; break;
	case TOK_ADD: v = eval(a->l) + eval(a->r); break;
	case TOK_SUB: v = eval(a->l) - eval(a->r); break;
	case TOK_MUL: v = eval(a->l) * eval(a->r); break;
	case TOK_DIV: v = eval(a->l) / eval(a->r); break;
	default: printf("internal error: bad node %c\n", a->nodetype);
	}
	return v;
}

void lex()
{
	while (pchSrcFront != pchSrcRear) {
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
		pchSrcFront = GET_SRC_POINT(pchSrcFront + 1);
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

struct ast * expr();

struct ast * term()
{
	struct ast * stAst;
	if (TOK_LBR == iToken) {
		match(TOK_LBR);
		stAst = expr();
		match(TOK_RBR);
	} else {
		stAst = newnum(iTokenValue);
		match(TOK_NUM);
	}
	return stAst;
}

struct ast * factor_tail(struct ast * stAstLeft)
{
	if (TOK_MUL == iToken) {
		match(TOK_MUL);
		struct ast * stAst = newast(TOK_MUL, stAstLeft, term());
		return factor_tail(stAst);
	} else if (TOK_DIV == iToken) {
		match(TOK_DIV);
		struct ast * stAst = newast(TOK_DIV, stAstLeft, term());
		return factor_tail(stAst);
	} else {
		return stAstLeft;
	}
}

struct ast * factor()
{
	struct ast * stAst = term();
	return factor_tail(stAst);
}

struct ast * expr_tail(struct ast * stAstLeft)
{
	if (TOK_ADD == iToken) {
		match(TOK_ADD);
		struct ast * stAst = newast(TOK_ADD, stAstLeft, factor());
		return expr_tail(stAst);
	} else if (TOK_SUB == iToken) {
		match(TOK_SUB);
		struct ast * stAst = newast(TOK_SUB, stAstLeft, factor());
		return expr_tail(stAst);
	} else {
		return stAstLeft;
	}
}

struct ast * expr()
{
	struct ast * stAst = factor();
	return expr_tail(stAst);
}

int main()
{
	pchSrc = pchSrcFront = pchSrcRear = (char *)malloc(SRC_BUF_SIZE);
	memset(pchSrc, 0, SRC_BUF_SIZE);
	
	while (1) {
		char c;
		do { 
			c = getc(stdin);
			if ('\r' == c || '\n' == c) {
				*pchSrcRear = '\n';
				pchSrcRear = GET_SRC_POINT(pchSrcRear + 1);
				break;
			} else {
				*pchSrcRear = c;
				pchSrcRear = GET_SRC_POINT(pchSrcRear + 1);
			}
		} while(1);
		
		lex();
		printf("= %d\n", eval(expr()));
	}
}
