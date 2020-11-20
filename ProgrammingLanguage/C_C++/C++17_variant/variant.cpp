#include <iostream>
#include <variant>

using namespace std;

struct A {
    A(int x) : a(x) {}
    int a;
};
struct B {
    B(int x, int y) : b(x), c(y) {}
    int b;
    int c;
};

typedef struct A struct_type_0;
typedef struct B struct_type_1;

int main()
{
    variant<struct_type_0,
            struct_type_1
    > var(A(1));
    cout << var.index() << endl;
    struct A a = get<0>(var);
    cout << a.a << endl;

    var = B(2, 3);
    cout << var.index() << endl;
    struct B b = get<1>(var);
    cout << b.b << " " << b.c << endl;
}