#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

void RandomChange(int *start, int *end)
{
	int size = (end - start);
	if (size < 2)
		return;
	int idx = rand() % size;
	swap(*(start + idx), *(end - 1));
}

int* Partition(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	int baseInt = *(end - 1);
	int *p1 = start;
	int *p2 = start;
	for (; p2 < end - 1; p2++)
		if (lt(*p2, baseInt))
			swap(*p2, *p1++);
	swap(*p2, *p1);

	return p1;
}

void QuickSort(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	if (start >= end -1)
		return;
	RandomChange(start, end);
	int *mid = Partition(start, end, lt);
	QuickSort(start, mid, lt);
	QuickSort(mid + 1, end, lt);
}

int main()
{
	int arr[LEN];

	srand(unsigned int(time(0)));
	generate(arr, arr + LEN, []()->int{ return rand() % 100; });
	//for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	for (int d : arr)
		cout << setw(3) << d;
	cout << endl;

	QuickSort(arr, arr + LEN, [](int a, int b){ return a < b; });
	//for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	for (int d : arr)
		cout << setw(3) << d;
	cout << endl;

	system("pause");

	return 0;
}
