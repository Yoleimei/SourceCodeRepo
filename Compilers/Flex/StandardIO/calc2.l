%{
	enum yytokentype {
		NUMBER = 258,
		ADD = 259,
		SUB = 260,
		MUL = 261,
		DIV = 262,
		EOL = 264
	};
	int yylval;
%}
%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\n      { return EOL; }
[ \t]   { /* ignore */ }
.       { printf("Mystery character %c\n", *yytext); }
%%
main(int argc, char **argv)
{
	int tok;
	while (tok = yylex()) {
		printf("%d", tok);
		if (NUMBER == tok)
			printf(" = %d\n", yylval);
		else
			printf("\n");
	}
}
