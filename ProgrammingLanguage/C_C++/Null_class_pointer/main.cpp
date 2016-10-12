#include <stdio.h>

struct aa
{
	int a;
	int b;
};

class Base
{
	Base():a(1){}
public:
	int a;
	void print() { printf("hello world%d\n", a); }
};

int main()
{
	struct aa aaa;
	aaa.a = 2;
	aaa.b = 3;
	Base *p = (Base *)&(aaa.b);
	p->print();
}
