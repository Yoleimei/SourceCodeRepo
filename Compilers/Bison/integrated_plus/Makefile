calc: calc.l calc.y calc.h
	bison -d calc.y
	flex -o calc.lex.c calc.l
	gcc -o $@ calc.tab.c calc.lex.c calc.c -lm

.PHONY clean:
	rm -f calc calc.lex.c calc.tab.c calc.tab.h
