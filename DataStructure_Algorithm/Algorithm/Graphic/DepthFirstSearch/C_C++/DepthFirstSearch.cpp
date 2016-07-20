#include <iostream>
#include <algorithm>

using namespace std;

const int LEN = 20;

void DfsVisit(int *adjacentMatrix, int startVertex, int n, int *visited, int *parent)
{
	visited[startVertex] = 1;
	for (int i = 0; i < n; i++)
	{
		if (adjacentMatrix[startVertex*n + i] > 0 && visited[i] == 0)
		{
			parent[i] = startVertex;
			DfsVisit(adjacentMatrix, i, n, visited, parent);
		}
	}
	cout << startVertex << " has accessed" << endl;
}

void DepthFirstSearch(int *adjacentMatrix, int n)
{
	// initial
	int visited[10];
	int parent[10];
	fill(visited, visited + n, 0);
	fill(parent, parent + n, -1);

	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 0)
			DfsVisit(adjacentMatrix, i, n, visited, parent);
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

	DepthFirstSearch(adjacentMatrix, n);

	fclose(stdin);
	fclose(stdout);
	//system("pause");

	return 0;
}
