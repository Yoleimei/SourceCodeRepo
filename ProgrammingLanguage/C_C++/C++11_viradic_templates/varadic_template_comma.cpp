#include <iostream>

using namespace std;

template<typename T>
void print(T t)
{
    cout << t << endl;
}

template<typename... Args>
void expand(Args... args)
{
    initializer_list<int>(print(args), 0)...;
}

int main()
{
    expand(1, 2, 3, 4);
}