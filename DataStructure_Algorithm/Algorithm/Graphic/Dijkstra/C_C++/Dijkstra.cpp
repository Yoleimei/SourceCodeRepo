#include <iostream>
#include <algorithm>

using namespace std;

const int LEN = 20;
const int MAX_VALUE = 999999999;

int ExtractMin(int n, int *visited, int *distance)
{
	int dis = MAX_VALUE;
	int minIdx = -1;
	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 0 && distance[i] < dis)
		{
			dis = distance[i];
			minIdx = i;
		}
	}

	return minIdx;
}

void Relax(int u, int v, int dis, int *distance, int *parent)
{
	if (distance[v] > distance[u] + dis)
	{
		distance[v] = distance[u] + dis;
		parent[v] = u;
	}
}

void PrintPath(int vertex, int *parent)
{
	if (parent[vertex] == -1)
	{
		cout << vertex;
		return;
	}
	PrintPath(parent[vertex], parent);
	cout << "->" << vertex;
}

void Dijkstra(int *adjacentMatrix, int startVertex, int n)
{
	// initial
	int visited[10];
	int parent[10];
	int distance[10];
	fill(visited, visited + n, 0);
	fill(parent, parent + n, -1);
	fill(distance, distance + n, MAX_VALUE);

	distance[startVertex] = 0;
	for (int i = 0; i < n; i++)
	{
		int vertex = ExtractMin(n, visited, distance);
		if (vertex == -1)
			continue;
		visited[vertex] = 1;
		for (int j = 0; j < n; j++)
		{
			if (adjacentMatrix[vertex*n + j] > 0 && visited[j] == 0)
				Relax(vertex, j, adjacentMatrix[vertex*n + j], distance, parent);
		}
	}

	for (int i = 0; i < n; i++)
	{
		PrintPath(i, parent);
		cout << endl;
	}
}

int main()
{
	int adjacentMatrix[100];

	FILE *stream;
	freopen_s(&stream, "Dijkstra.txt", "r", stdin);
	freopen_s(&stream, "out.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i < n*n; i++)
		cin >> adjacentMatrix[i];

	Dijkstra(adjacentMatrix, 0, n);

	fclose(stdin);
	fclose(stdout);
	//system("pause");

	return 0;
}
