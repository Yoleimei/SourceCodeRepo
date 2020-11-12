#include <iostream>
#include <future>
#include <chrono>

using namespace std;

bool is_prime(int x)
{
    for (int i = 2; i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}

int  main()
{
    int num = 444444443;
    futurn<bool> fut = async(is_prime, num);
    chrono::milliseconds span(100);
    while (fut.wait_for(span) == future_status::timeout)
    {
        cout << "." << flush;
    }
    bool x = fut.get();
    cout << endl << num << (x ? " is" : " is not") << " prime" << endl;

    return 0;
}