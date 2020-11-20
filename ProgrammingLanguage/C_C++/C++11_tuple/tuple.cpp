#include <iostream>
#include <tuple>

using namespace std;

int main()
{
    tuple<char, short> foo1('1', 2);
    tuple<char, short, int> foo2 = make_tuple('3', 4, 5);

    cout << get<0>(foo1) << endl;
    cout << get<1>(foo1) << endl;
    cout << get<0>(foo2) << endl;
    cout << get<1>(foo2) << endl;
    cout << get<2>(foo2) << endl;
}