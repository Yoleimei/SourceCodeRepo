#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

const int LEN = 20;

struct Node
{
	int data;
	Node *next;

	Node(int d, Node *n=NULL) : data(d), next(n) {}
};

void BucketSort(int *start, int *end, const function<bool(int a, int b)> &lt)
{
	Node *bucket[LEN];
	for (int i = 0; i < LEN; i++)
		bucket[i] = NULL;
	for (int *p = start; p < end; p++)
	{
		int idx = *p / 5;
		if (bucket[idx] == NULL)
			bucket[idx] = new Node(*p);
		else
		{
			Node *p1 = bucket[idx];
			while (p1->next != NULL && lt(p1->data, *p))
				p1 = p1->next;
			Node *p2 = p1->next;
			p1->next = new Node(*p);
			p1->next->next = p2;
		}
	}
	int idx = 0;
	for (int i = 0; i < LEN; i++)
	{
		Node *p = bucket[i];
		while (p != NULL)
		{
			*(start + idx++) = p->data;
			p = p->next;
		}
	}
}

int main()
{
	int arr[LEN];

	srand(unsigned int(time(0)));
	generate(arr, arr + LEN, []()->int{ return rand() % 100; });
	for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	BucketSort(arr, arr + LEN, [](int a, int b){ return a < b; });
	for_each(arr, arr + LEN, [](int d){ cout << setw(3) << d; });
	cout << endl;

	system("pause");

	return 0;
}
