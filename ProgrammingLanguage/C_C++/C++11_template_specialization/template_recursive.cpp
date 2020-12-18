#include <cstdio>

template<int N>
class Sum
{
public:
    enum { sum = Sum<N-1>::sum + N; }
};

template<>
class Sum<0>
{
public:
    enum { sum = 0; }
}
