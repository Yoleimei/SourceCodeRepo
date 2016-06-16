#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

void InsertSort(int *start, int *end, const function<bool (int a, int b)> &lt)
{
	if (start == end)
		return;
	for(int *p1=start+1; p1<end; p1++)
	{
		int baseInt = *p1;
		int *p2 = p1 - 1;
		for(; p2 >= start && lt(baseInt, *p2) ;p2--)
			*(p2+1) = *p2;
		*(p2+1) = baseInt;
	}
}

int main()
{
	int arr[LEN];

	srand(unsigned int(time(0)));
	generate(arr, arr+LEN, []()->int{ return rand() % 100; });
	for_each(arr, arr+LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	InsertSort(arr, arr+LEN, [](int a, int b){ return a < b; });
	for_each(arr, arr+LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	system("pause");

	return 0;
}
