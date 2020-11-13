#include <iostream>

using namespace std;

struct A
{
    A(int i) : m_i(i) {}
    ~A() {}
    int m_i;
    void print() { cout << m_i << endl; }
};

struct B
{
    B(int i ,double d) : m_i(i), m_d(d) {}
    ~B()
    int m_i;
    int m_d;
    void print() { cout << m_i << " " << m_d << endl; }
};

template<typename T, typename... Args>
T* Instance(Args&&... args)
{
    // return new T(std::forward<Args>(args)...);
    return new T(args...);
}

int main()
{
    A* pa = Instance<A>(1);
    pa->print();

    B* pb = Instance<B>(1, 2.0);
    pb->print();
}