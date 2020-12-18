#include <cstdio>

template<typename T>
class Test
{
public:
    Test() {}
    ~Test() {}
    T add(T arg1, T arg2) { return arg1 + arg2; }
}

template<>
class Test<int>
{
public:
    Test();
    ~Test();
    int add(int arg1, int arg2) { return arg1 + arg2; }
}

Test<int>::Test()
{
    
}

Test<int>::~Test()
{
    
}

int main()
{
    Test<int> test;
    printf("%d\n", test.add(1, 2));
}