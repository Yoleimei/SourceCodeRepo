#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

void CountingSort(int *arr, int num, int k)
{
	int *arrB = new int[num];
	int *arrC = new int[k];
	generate(arrB, arrB + num, []()->int{return 0; });
	generate(arrC, arrC + k, []()->int{return 0; });
	for (int i = 0; i < num; ++i)
		++arrC[arr[i]];
	for (int i = 1; i < k; ++i)
		arrC[i] = arrC[i] + arrC[i - 1];
	for (int i = num - 1; i >= 0; --i) {
		arrB[arrC[arr[i]]-1] = arr[i];
		arrC[arr[i]] = arrC[arr[i]] - 1;
	}
	for (int i = 0; i < num; ++i) arr[i] = arrB[i];
	delete[] arrB;
	delete[] arrC;
}

int main()
{
	int arr[LEN];

	srand(unsigned int(time(0)));
	generate(arr, arr + LEN, []()->int{ return rand() % 100; });
	for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	CountingSort(arr, LEN, 100);
	for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	system("pause");

	return 0;
}
