#include <iostream>

using namespace std;

template <typename T>
void print(T t)
{
    cout << t << endl;
}

int main()
{
    print('A');
    print(1);
    print(2.0);
    print("Hello world!");
}