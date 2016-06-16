#include <iostream>

using namespace std;

//Comparable必须重载 ① '>' ② '<' ③ '==' ④ '<<'
template <typename Comparable>
class SplayTree
{
public:
	SplayTree() 
	{ 
		root = NULL;
	}

	~SplayTree() 
	{ 
		makeEmpty(); 
	}
	
	bool isEmpty()
	{
		return root ? false : true;
	}
	
	void makeEmpty()
	{
		makeEmpty(root);
	}

	bool search(Comparable d)
	{
		if (!root)
			return false;
		root = splay(d, root);
		if (d == root->data)
			return true;
		return false;
	}

	void insert(Comparable d)
	{
		BinaryTreeNode *newNode = new BinaryTreeNode(d);
		
		if (root == NULL)
			root = newNode;
		else
		{
			root = splay(d, root);
			if (d < root->data)
			{
				newNode->left = root->left;
				newNode->right = root;
				root->left = NULL;
				root = newNode;
			}
			else if (d > root->data)
			{
				newNode->right = root->right;
				newNode->left = root;
				root->right = NULL;
				root = newNode;
			}
			else
				return;
		}
	}
	
	void remove(Comparable d)
	{
		if (root)
		{
			root = splay(d, root);

			if (d == root->data)
			{
				BinaryTreeNode *newRoot = NULL;

				if (!root->left)
				{
					newRoot = root->right;
				}
				else
				{
					newRoot = root->left;
					newRoot = splay(d, newRoot);
					newRoot->right = root->right;
				}
				delete root;
				root = newRoot;
			}
		}
	}
	
	void printTree()
	{
		if (root)
		{
			printTree(root);
			cout << endl;
		}
		else
			cout << "树中没有数据" << endl;
	}

private:
	struct BinaryTreeNode
	{
		Comparable data;
		BinaryTreeNode *left;
		BinaryTreeNode *right;
		
		BinaryTreeNode(Comparable d, BinaryTreeNode *l=NULL, BinaryTreeNode *r=NULL): data(d), left(l), right(r) {  }
	};

	BinaryTreeNode *root;
	
	void makeEmpty(BinaryTreeNode *&n) // 需要改变指针参数
	{
		if (n)
		{
			makeEmpty(n->left);
			makeEmpty(n->right);
			delete n;
			n = NULL;
		}
		return;
	}
	
	void printTree(BinaryTreeNode *r)
	{
		if (!r)
			return;
		printTree(r->left);
		cout << r->data << " ";
		printTree(r->right);
	}
	
	void rotateWithLeftChild(BinaryTreeNode *&n)
	{
		BinaryTreeNode *k1 = n->left;
		BinaryTreeNode *k2 = n;
		k2->left = k1->right;
		k1->right = k2;
		n = k1;
	}
	
	void rotateWithRightChild(BinaryTreeNode *&n)
	{
		BinaryTreeNode *k1 = n;
		BinaryTreeNode *k2 = n->right;
		k1->right = k2->left;
		k2->left = k1;
		n = k2;
	}

	BinaryTreeNode* splay(Comparable d, BinaryTreeNode *midTreeRoot)
	{
		static BinaryTreeNode header(0);
		header.left = header.right = NULL;

		BinaryTreeNode *leftTreeMax, *rightTreeMin;
		leftTreeMax = rightTreeMin = &header;
		
		cout << "start splaying:" << endl;

		while (midTreeRoot->data != d)
		{
			if (d < midTreeRoot->data)
			{
				if (midTreeRoot->left == NULL)
					break;
				if (d < midTreeRoot->left->data && midTreeRoot->left->left)  // zig-zig
					rotateWithLeftChild(midTreeRoot);
				// 右连接
				rightTreeMin->left = midTreeRoot;
				rightTreeMin = midTreeRoot;
				midTreeRoot = midTreeRoot->left;
				rightTreeMin->left = NULL;
			}
			else if (d > midTreeRoot->data)
			{
				if (midTreeRoot->right == NULL)
					break;
				if (d > midTreeRoot->right->data && midTreeRoot->right->right)  // zig-zig
					rotateWithRightChild(midTreeRoot);
				// 左连接
				leftTreeMax->right = midTreeRoot;
				leftTreeMax = midTreeRoot;
				midTreeRoot = midTreeRoot->right;
				leftTreeMax->right = NULL;
			}
			else
				break;
		}

		cout << "before reassembling:" << endl;
		cout << "L-Tree: ";
		printTree(header.right);
		cout << endl;
		cout << "M-Tree: ";
		printTree(midTreeRoot);
		cout << endl;
		cout << "R-Tree: "; 
		printTree(header.left);
		cout << endl;

		leftTreeMax->right = midTreeRoot->left;
		rightTreeMin->left = midTreeRoot->right;
		midTreeRoot->left = header.right;
		midTreeRoot->right = header.left;
		
		cout << "after reassembling:" << endl;
		cout << "M-Tree: ";
		printTree(midTreeRoot);
		cout << endl;

		return midTreeRoot;
	}
};
