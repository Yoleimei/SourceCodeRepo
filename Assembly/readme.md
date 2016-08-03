add.s: 用汇编完成如下C函数
int add(int a, int b)
{
	return a + b;
}

提示:
.global _add
iret

main.c: 调用add.s中的_add子程序
