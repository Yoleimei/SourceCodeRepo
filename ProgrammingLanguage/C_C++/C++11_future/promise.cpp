#include <iostream>
#include <future>
#include <chrono>

using namespace std;

void print_int(future<int>& fut)
{
    int x = fut.get();
    cout << "value: " << x << endl;
}

int main()
{
    promise<int> prom;
    future<int> fut = prom.get_future();
    thread th(print_int, ref(fut));
    this_thread::sleep_for(chrono::seconds(2));
    prom.set_value(5);
    th.join();

    return 0;
}