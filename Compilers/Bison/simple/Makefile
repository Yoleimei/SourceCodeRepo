calc: calc.l calc.y
	bison -d calc.y  # calc.tab.h calc.tab.c
	flex calc.l      # lex.yy.c
	gcc -o $@ calc.tab.c lex.yy.c -lfl

.PHONY clean:
	rm -f calc *.tab.* lex.*