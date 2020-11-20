#include <iostream>
#include <typeindex>
#include <unordered_map>

using namespace std;

struct TestA {
    TestA(int a) : x(a) {}
    int x;
};
struct TestB {
    TestB(int b) : y(b) {}
    int y;
};
unordered_map<type_index, int> struct_to_type_mapping = {
    { typeid(TestA), 0 },
    { typeid(TestB), 1 }
};

int main()
{
    auto a = TestA(1);
    auto b = TestB(2);
    cout << struct_to_type_mapping[typeid(decltype(a))] << endl;
    cout << struct_to_type_mapping[typeid(decltype(b))] << endl;
}