calc: calc.l calc.y calc.h
	bison -d calc.y                            # calc.tab.h  calc.tab.c
	flex -o calc.lex.c calc.l                  # calc.lex.c
	gcc -o $@ calc.tab.c calc.lex.c calc.c -lm # calc

.PHONY clean:
	rm -f calc calc.lex.c calc.tab.c calc.tab.h
