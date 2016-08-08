calc: calc.l calc.y
	bison -d calc.y
	flex calc.l
	gcc -o $@ calc.tab.c lex.yy.c -lfl
