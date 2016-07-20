#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

void MakeHeap(int *start, int parentIdx, int size, const function<bool(int a, int b)> &lt)
{
	int childIdx = 2 * parentIdx + 1;
	while (childIdx < size)
	{
		if (childIdx + 1 < size && lt(start[childIdx], start[childIdx + 1]))
			childIdx++;
		if (lt(start[parentIdx], start[childIdx]))
		{
			swap(start[parentIdx], start[childIdx]);
			parentIdx = childIdx;
			childIdx = 2 * parentIdx + 1;
		}
		else
			break;
	}
}

void HeapSort(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	int size = end - start;
	int parentIdx = (size - 1) / 2;
	for (int p = parentIdx; p >= 0; p--)
	{
		MakeHeap(start, p, size, lt);
	}
	while (true)
	{
		swap(start[--size], start[0]);
		if (size < 2)
			break;
		MakeHeap(start, 0, size, lt);
	}
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

	HeapSort(arr, arr + LEN, [](int a, int b){ return a < b; });
	//for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	for (int d : arr)
		cout << setw(3) << d;
	cout << endl;

	system("pause");

	return 0;
}
