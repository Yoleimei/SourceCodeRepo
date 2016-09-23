<expr> ::=
	<factor> <expr_tail>  // <factor>的优先级高
	;
<expr_tail> ::=
	<empty>
	| '+' <factor> <expr_tail> // <factor>的优先级高
	| '-' <factor> <expr_tail>
	;
<factor> ::=
	<term> <factor_tail>  // <term>的优先级高
	;
<factor_tail> ::=
	<empty>
	| '*' <term> <factor_tail>
	| '-' <term> <factor_tail>
	;
<term> ::=
	NUMBER
	| '(' <expr> ')'
	;
