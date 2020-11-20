#include <iostream>
#include <optional>

using namespace std;

int main()
{
    optional<int> a = { 1 };
    optional<int> b = {};
    optional<int> c = { nullopt };

    cout << a.has_value() << endl;
    cout << b.has_value() << endl;
    cout << c.has_value() << endl;
}