#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_VALUE = 999999999;

struct HuffmanNode
{
	int weight;
	char ch;
	string code;
	HuffmanNode *left;
	HuffmanNode *right;

	HuffmanNode(
		int w, 
		char c, 
		string s = "", 
		HuffmanNode *l = nullptr, 
		HuffmanNode *r = nullptr
	): weight(w), ch(c), code(s), left(l),right(r) {}
};

struct HuffmanNodeGreater
{
	bool operator()(const HuffmanNode &a, const HuffmanNode &b)
	{
		return a.weight > b.weight;
	}
};

void ConstructHuffmanTree(priority_queue<HuffmanNode, vector<HuffmanNode>, HuffmanNodeGreater> &HuffmanRoot)
{
	while (HuffmanRoot.size() > 1)
	{
		HuffmanNode *left = new HuffmanNode(HuffmanRoot.top());
		HuffmanRoot.pop();
		HuffmanNode *right = new HuffmanNode(HuffmanRoot.top());
		HuffmanRoot.pop();

		HuffmanNode parent(left->weight + right->weight, ' ');
		parent.left = left;
		parent.right = right;
		HuffmanRoot.push(parent);
	}
}

void InOrderTraversal(HuffmanNode *node, vector<HuffmanNode> &vec, string &str)
{
	if (node->left == NULL && node->right == NULL)
	{
		vec.push_back(HuffmanNode(node->weight, node->ch, str));
		return;
	}
	if (node->left)
	{
		str.push_back('0');
		InOrderTraversal(node->left, vec, str);
		str.pop_back();
	}
	if (node->right)
	{
		str.push_back('1');
		InOrderTraversal(node->right, vec, str);
		str.pop_back();
	}
}

void HuffmanCoding(const priority_queue<HuffmanNode, vector<HuffmanNode>, HuffmanNodeGreater> &HuffmanRoot, vector<HuffmanNode> &vec)
{
	HuffmanNode node(HuffmanRoot.top());
	string str = "";
	InOrderTraversal(&node, vec, str);
}

int main()
{
	priority_queue<HuffmanNode, vector<HuffmanNode>, HuffmanNodeGreater> HuffmanRoot;
	HuffmanRoot.push(HuffmanNode(1, 'a'));
	HuffmanRoot.push(HuffmanNode(2, 'b'));
	HuffmanRoot.push(HuffmanNode(3, 'c'));
	HuffmanRoot.push(HuffmanNode(4, 'd'));
	HuffmanRoot.push(HuffmanNode(5, 'e'));
	ConstructHuffmanTree(HuffmanRoot);
	vector<HuffmanNode> vec;
	HuffmanCoding(HuffmanRoot, vec);
	for (HuffmanNode node : vec)
		cout << node.ch << " " << node.code << endl;

	system("pause");

	return 0;
}