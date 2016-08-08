%{
#include <stdio.h>
%}

%token NUMBER
%token ADD SUB MUL DIV
%token LBRACKET RBRACKET
%token EOL

%%

calclist:
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
	| LBRACKET exp RBRACKET { $$ = $2; }
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
