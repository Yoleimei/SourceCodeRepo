%{
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
%}

// extern YYSTYPE yylval;
// %union 改变 YYSTYPE 的结构，默认为int
%union {
	struct ast *a;
	double d;
}

%token <d> NUMBER          // <d>语法符号使用的值类型
%token EOL
%type <a> exp factor term  // <a>定义类型 

%% 

calclist:
	| calclist exp EOL	{
							printf("= %4.4g\n", eval($2));
							treefree($2);
							printf("> ");
						}
	| calclist EOL		{ printf("> "); }
	;
exp: factor
	| exp '+' factor	{ $$ = newast('+', $1, $3); }
	| exp '-' factor	{ $$ = newast('-', $1, $3); }
	;
factor: term
	| factor '*' term	{ $$ = newast('*', $1, $3); }
	| factor '/' term	{ $$ = newast('/', $1, $3); }
	;
term: NUMBER			{ $$ = newnum($1); }
	| '(' exp ')'		{ $$ = $2; }  /*  */
	| '|' term '|'		{ $$ = newast('|', $2, NULL); }
	| '-' term			{ $$ = newast('M', $2, NULL); }
	;

%%
