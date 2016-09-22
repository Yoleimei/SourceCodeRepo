(包含左递归的四则运算BNF范式)
<expr> ::=
	<factor>
	| <expr> '+' <factor>
	| <expr> '-' <factor>
	;
<factor> ::=
	<term>
	| <factor> '*' <term>
	| <factor> '/' <term>
	;
<term> ::=
	NUMBER
	| '(' <expr> ')'
	;

(消除左递归后的四则运算BNF范式)
<expr> ::=
	<factor> <expr_tail>
	;
<expr_tail> ::=
	<empty>
	| '+' <factor> <expr_tail>
	| '-' <factor> <expr_tail>
	;
<factor> ::=
	<term> <factor_tail>
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

用<>括起来的是"非终结符"，可以用 ::= 右边的式子代替，如: expr, factor, term
没有出现在 ::= 左边的就称为"终结符"，如: '+', '-', '*', '/', '(', ')', NUMBER

自顶向下: 从起始非终结符开始，不断对非终结符进行分解，直到匹配输入的终结符
自底向上: 不断对终结符进行合并，直到合并成起始地非终结符
递归下降法 就是自顶向下的方法，自定向下的语法分析方法不能处理左递归的文法。
LL(1)文法 是不带回溯的自顶向下的文法

(1) 消除二义性
<statement> ::= 
	if <expression> then <statement>  |
	if <expression> then <statement> else <statement>  |
	other
	;
==>
<statement> ::=
	matched_statement  |
	open_statement  ;
<matched_statement> ::=
	if <expression> then <matched_statement> else <matched_statement>  |
	other  ;
<open_statement> ::=
	if <expression> then <statement>  |
	if <expression> then <matched_statement> else <open_statement>  ;
(2) 消除左递归
左递归: 如果一个文法中有一个非终结符号A使得对某个串α存在一个推导 A ::= Aα, 那么这个文法就是左递归的
A ::= Aα | β  ;
==>
A ::= βA'  ;
A' ::= αA' | ε  ;
=========================
A ::= Aα1 | Aα2 | ... | Aαm | β1 | β2 | ... | βn  ;
==>
A ::= β1A' | β2A' | ... | βnA'  ;
A' ::= α1A' | α2A' | ... | αmA' | ε  ;
(3) 提取左公因式
A ::= αβ1 | αβ2  ;
==>
A ::= αA'  ;
A' ::= β1 | β2  ;
