%{
#include "calc.tab.h"
%}
%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"("     { return LBRACKET; }
")"     { return RBRACKET; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\n      { return EOL; }
[ \t]   { /* ignore */ }
.       { printf("Mystery character %c\n", *yytext); }
%%

