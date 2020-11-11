#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int substract(int x, int y)
{
    return x - y;
}

decltype(&add) func;

void register_func(decltype(&add) f)
{
    func = f;
}

void foo_print(int x, int y)
P
{
    std::cout << x << " func " << y " is " << func(x, y) << std::endl;
}

int main()
{
    int a = 4;
    decltype(a) b = 3;

    register_func(add);
    foo_print(a, b);

    register_func(substract);
    foo_print(a, b);

    return 0;
}