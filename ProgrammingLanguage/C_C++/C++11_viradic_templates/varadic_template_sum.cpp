#include <iostream>

using namespace std;

template<class T>
void sum(T t)
{
    return t;
}

template<class T, class... Args>
void sum(T first, Args... rest)
{
    return first + sum<T>(rest);
}

int main()
{
    int sum_ = sum(1, 2, 3, 4);
    cout << sum_ << endl;
}