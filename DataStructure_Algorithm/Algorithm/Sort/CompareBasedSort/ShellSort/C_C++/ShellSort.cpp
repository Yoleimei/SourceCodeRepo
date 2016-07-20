#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

// Sedgewick
// 9 * 4^i - 9 * 2^i + 1 -- 1, 19, 109
// 2^(i+2) * (2^(i+2) -3) + 1 -- 5, 41
struct GenerateSedgewick1
{
	int current;
	GenerateSedgewick1() { current = -1; }
	int operator()()
	{
		current++;
		return int(9 * pow(4, current) - 9 * pow(2, current) + 1);
	}
} GenFun1;

struct GenerateSedgewick2
{
	int current;
	GenerateSedgewick2() { current = -1; }
	int operator()()
	{
		current++;
		return int(pow(2, current + 2) * (pow(2, current + 2) - 3) + 1);
	}
} GenFun2;

void InsertSort(int *start, int *end, int step, const function<bool(int a, int b)> &lt)
{
	if (start == end)
		return;
	for (int *p1 = start + step; p1<end; p1 += step)
	{
		int baseInt = *p1;
		int *p2 = p1 - step;
		for (; p2 >= start && lt(baseInt, *p2); p2 -= step)
			*(p2 + step) = *p2;
		*(p2 + step) = baseInt;
	}
}

void ShellSort(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	const int SedgewickLen = 5;
	int size = end - start;
	int step;
	int Sedgewick1[SedgewickLen], Sedgewick2[SedgewickLen], Sedgewick[2*SedgewickLen];
	generate(Sedgewick1, Sedgewick1 + SedgewickLen, GenFun1);
	generate(Sedgewick2, Sedgewick2 + SedgewickLen, GenFun2);
	merge(Sedgewick1, Sedgewick1 + SedgewickLen, Sedgewick2, Sedgewick2 + SedgewickLen, Sedgewick);
	for (int i = 2 * SedgewickLen - 1; i >= 0; i--)
	{
		step = Sedgewick[i];
		if (step <= size / 2)
			InsertSort(start, end, step, lt);
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

	ShellSort(arr, arr + LEN, [](int a, int b){ return a < b; });
	//for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	for (int d : arr)
		cout << setw(3) << d;
	cout << endl;

	system("pause");

	return 0;
}
