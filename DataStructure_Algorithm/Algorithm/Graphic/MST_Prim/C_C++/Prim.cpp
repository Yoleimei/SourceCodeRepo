#include <iostream>
#include <iomanip>
#include <deque>
#include <algorithm>

using namespace std;

const int MAX_VALUE = 999999999;
const int VERTEX_NUM = 4;

int adjacentMatrix[VERTEX_NUM*VERTEX_NUM];

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

int Prim(int *adjacentMatrix, int n)
{
	int result = 0;

	int parent[VERTEX_NUM];
	int visited[VERTEX_NUM];
	int distance[VERTEX_NUM];
	fill(parent, parent + VERTEX_NUM, -1);
	fill(visited, visited + VERTEX_NUM, 0);
	fill(distance, distance + VERTEX_NUM, MAX_VALUE);

	distance[0] = 0;
	for (int i = 0; i < n;i++)
	{
		int vertex = ExtractMin(n, visited, distance);
		if (vertex == -1)
			break;
		visited[vertex] = 1;
		result += distance[vertex];
		for (int i = 0; i < n; i++)
		{
			if (adjacentMatrix[vertex*n + i] > 0 && visited[i] == 0 && adjacentMatrix[vertex*n + i] < distance[i])
			{
				parent[i] = vertex;
				distance[i] = adjacentMatrix[vertex*n + i];
			}
		}
	}

	return result;
}

int main()
{
	FILE *stream;
	freopen_s(&stream, "Kruskal.txt", "r", stdin);
	freopen_s(&stream, "out.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i < n*n; i++)
		cin >> adjacentMatrix[i];

	cout << Prim(adjacentMatrix, n) << endl;

	fclose(stdin);
	fclose(stdout);
	//system("pause");

	return 0;
}
