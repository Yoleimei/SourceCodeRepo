#include <iostream>

using namespace std;

template<class T>
void print(T t)
{
    cout << t << endl;
}

template<class T, class... Args>
void print(T head, Args... rest)
{
    cout << head << endl;
    print(rest...);
}

int main()
{
    print(1, 2, 3, 4);
}