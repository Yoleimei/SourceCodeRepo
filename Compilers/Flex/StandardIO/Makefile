test: 
	flex -Cf test.l
	gcc lex.yy.c -o test -lfl

calc1: 
	flex -Cf calc1.l
	gcc lex.yy.c -o calc1 -lfl

calc2: 
	flex -Cf calc2.l
	gcc lex.yy.c -o calc2 -lfl

.PHONY clean:
	rm -f test calc1 calc2 lex.yy.c

# -Cf 不压缩状态转移矩阵
