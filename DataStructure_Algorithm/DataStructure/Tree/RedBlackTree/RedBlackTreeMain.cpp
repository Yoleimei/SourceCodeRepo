#include <ctime>
#include <iostream>
#include <cstdlib>

#include "RedBlackTree.hpp"

using namespace std;

const int LENGTH = 8;

void generateTree(RedBlackTree *tree)
{
	srand((unsigned int)time(NULL));
	int i = LENGTH;
	while(i--)
	{
		tree->insert(rand() % 100);
		tree->printTree();
	}
}

void checkRemove(RedBlackTree *tree)
{
	while (!tree->isEmpty())
	{
		int elem;
		cout << "请输入要移除的数据: ";
		cin >> elem;
		tree->remove(elem);
		tree->printTree();

	}
}

int main()
{
	RedBlackTree *tree = new RedBlackTree(); 
	generateTree(tree);
	tree->printTree();

	checkRemove(tree);

	system("pause");
}
