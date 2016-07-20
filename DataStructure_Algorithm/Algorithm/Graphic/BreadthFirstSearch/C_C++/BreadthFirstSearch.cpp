#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int LEN = 20;


void BreadthFirstSearch(int *adjacentMatrix, int n)
{
	// initial
	int visited[10];
	int parent[10];
	fill(visited, visited + n, 0);
	fill(parent, parent + n, -1);
	queue<int> myQue;

	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 1)
			continue;
		visited[i] = 1;
		parent[i] = -1;
		myQue.push(i);
		while (!myQue.empty())
		{
			int u = myQue.front();
			cout << u << " has accessed" << endl;
			myQue.pop();
			for (int i = 0; i < n; i++)
			{
				if (adjacentMatrix[u*n + i] >0 && visited[i] == 0)
				{
					myQue.push(i);
					visited[i] = 1;
					parent[i] = u;
				}
			}
		}
	}
}

int main()
{
	int adjacentMatrix[100];

	FILE *stream;
	freopen_s(&stream, "DepthFirstSearch.txt", "r", stdin);
	freopen_s(&stream, "out.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i < n*n; i++)
		cin >> adjacentMatrix[i];

	BreadthFirstSearch(adjacentMatrix, n);

	fclose(stdin);
	fclose(stdout);
	//system("pause");

	return 0;
}
