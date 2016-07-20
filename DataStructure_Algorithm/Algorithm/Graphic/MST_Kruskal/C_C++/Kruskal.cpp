#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
	int u;
	int v;
	int weight;

	Edge(int u, int v, int w) : u(u), v(v), weight(w) {}

	bool operator < (Edge &e)
	{
		return weight < e.weight;
	}
};

const int VERTEX_NUM = 4;

int adjacentMatrix[VERTEX_NUM*VERTEX_NUM];
int parent[VERTEX_NUM];
int dsRank[VERTEX_NUM];

void MakeSet(int x)
{
	parent[x] = x;
	dsRank[x] = 0;
}

int FindSet(int x)
{
	if (x != parent[x])
		parent[x] = FindSet(parent[x]);
	return parent[x];
}

void Link(int x, int y)
{
	if (dsRank[x] > dsRank[y])
		parent[y] = x;
	else
	{
		parent[y] = x;
		if (dsRank[x] == dsRank[y])
			dsRank[x] = dsRank[x] + 1;
	}
}

void Union(int x, int y)
{
	Link(FindSet(x), FindSet(y));
}

int Kruskal(int *adjacentMatrix, int n)
{
	vector<Edge> edge;
	for (int i = 0; i < n; i++)
	{
		MakeSet(i);
		for (int j = i + 1; j < n; j++)
		{
			if (adjacentMatrix[i*n + j] > 0)
				edge.push_back(Edge(i, j, adjacentMatrix[i*n + j]));
		}
	}
	sort(edge.begin(), edge.end());
	int result = 0;
	for (auto it = edge.begin(); it != edge.end(); it++)
	{
		int u = it->u;
		int v = it->v;
		if (FindSet(u) != FindSet(v))
		{
			Union(u, v);
			result += it->weight;
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

	cout << Kruskal(adjacentMatrix, n) << endl;

	fclose(stdin);
	fclose(stdout);
	//system("pause");

	return 0;
}
