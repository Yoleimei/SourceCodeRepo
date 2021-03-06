%{
#include <stdio.h>
%}

%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%

calclist: /* 空规则，代表从开头进行匹配 */
	| calclist exp EOL { printf("= %d\n", $2); }
	;
	
exp: factor { $$ = $1; }
	| exp ADD factor { $$ = $1 + $3; }
	| exp SUB factor { $$ = $1 - $3; }
	;
	
factor: term { $$ = $1; }
	| factor MUL term { $$ = $1 * $3; }
	| factor DIV term { $$ = $1 / $3; }
	;

term: NUMBER { $$ = $1; }
	;
	
%%

main(int argc, char **argv)
{
	yyparse();
}
yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}
