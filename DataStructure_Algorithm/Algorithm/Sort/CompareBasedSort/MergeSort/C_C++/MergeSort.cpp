#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

void merge(int *start, int *mid, int *end, const function<bool(int a, int b)> &lt)
{
	int *tmp = new int[end - start];
	int *p1 = start;
	int *p2 = mid;
	int *p3 = tmp;

	while (p1 < mid && p2 < end)
	{
		while (p1 < mid && !lt(*p2, *p1))
			*p3++ = *p1++;
		while (p2 < end && !lt(*p1, *p2))
			*p3++ = *p2++;
	}

	while (p1 < mid)
		*p3++ = *p1++;
	while (p2 < end)
		*p3++ = *p2++;
	for (int i = 0; i < end - start; i++)
		start[i] = tmp[i];

	delete[] tmp;
}

void MergeSort(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	if (end - start <= 1)
		return;
	int *mid = start + (end - start) / 2;
	MergeSort(start, mid, lt);
	MergeSort(mid, end, lt);
	merge(start, mid, end, lt);
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

	MergeSort(arr, arr + LEN, [](int a, int b){ return a < b; });
	//for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	for (int d : arr)
		cout << setw(3) << d;
	cout << endl;

	system("pause");

	return 0;
}
