#include <iostream>

using namespace std;

//Comparable必须重载 ① '>' ② '<' ③ '==' ④ '<<'
template <typename Comparable>
class AvlTree
{
public:
	AvlTree() { root = NULL; }
	AvlTree(const AvlTree *bst) { root = deepClone(bst->root); }
	~AvlTree() { makeEmpty(); }
	
	AvlTree* operator=(const AvlTree *bst)
	{
		this->root = deepClone(bst->root);
		return this;
	}
	
	Comparable findMin()
	{
		// 方法一
		BinaryTreeNode *r = root;
		BinaryTreeNode *p = NULL;
		while (r)
		{
			p = r;
			r = r->left;
		}
		if (p)
			return p->data;
		else
			return -1;
		// 方法二
		//return findMinNode(root)->data;
	}
	
	Comparable findMax()
	{
		// 方法一
		BinaryTreeNode *r = root;
		BinaryTreeNode *p = NULL;
		while (r)
		{
			p = r;
			r = r->right;
		}
		if (p)
			return p->data;
		else
			return -1;
		// 方法二
		//return findMaxNode(root)->data;
	}
	
	bool contains(Comparable d)
	{
		// 方法一
		BinaryTreeNode *r = root;
		while (r)
		{
			if (d < r->data)
				r = r->left;
			else if (d > r->data)
				r = r->right;
			else
				return true;
		}
		return false;
		// 方法二
		//return searchNode(d) ? true : false;
	}
	
	Comparable findPredecessor(Comparable d)
	{
		BinaryTreeNode *n = searchNode(d);
		if (n)
		{
			BinaryTreeNode *pre = findPredeNode(n);
			
			if (pre)
				return pre->data;
			else
				return n->data;
		}
		else
			return d;
	}
	
	Comparable findSuccessor(Comparable d)
	{
		BinaryTreeNode *n = searchNode(d);
		if (n)
		{
			BinaryTreeNode *suc = findSucNode(n);
			
			if (suc)
				return suc->data;
			else
				return n->data;
		}
		else
			return d;
	}
	
	bool isEmpty()
	{
		return root ? false : true;
	}
	
	void makeEmpty()
	{
		makeEmpty(root);
	}

	void insert(Comparable d)
	{
		if (root)
			insertNode(d, root);
		else
			root = new BinaryTreeNode(d);
		
		root->height = maxHeight(root);
	}
	
	void remove(Comparable d)
	{
		BinaryTreeNode *n = searchNode(d);
		
		if (n != NULL)
		{
			removeNode(n);
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
		BinaryTreeNode *parent;
		int height;
		
		BinaryTreeNode(Comparable d, BinaryTreeNode *l=NULL, BinaryTreeNode *r=NULL, BinaryTreeNode *p=NULL, int h=0): data(d), left(l), right(r), parent(p), height(h) { }
	};

	BinaryTreeNode *root;
	
	BinaryTreeNode* deepClone(BinaryTreeNode *n)
	{
		if (n)
		{
			BinaryTreeNode *p = new BinaryTreeNode(n->data, deepClone(n->left), deepClone(n->right), NULL, n->height);
			if (p->left)
				p->left->parent = p;
			if (p->right)
				p->right->parent = p;
			return p;
		}
		return NULL;
	}
	
	BinaryTreeNode* findMinNode(BinaryTreeNode *n)
	{
		if (n->left)
			return findMinNode(n->left);
		return n;
	}
	
	BinaryTreeNode* findMaxNode(BinaryTreeNode *n)
	{
		if (n->right)
			return findMaxNode(n->right);
		return n;
	}

	BinaryTreeNode* searchNode(Comparable d)
	{
		BinaryTreeNode *r = root;
		while (r)
		{
			if (d < r->data)
				r = r->left;
			else if (d > r->data)
				r = r->right;
			else
				return r;
		}
		return NULL;
	}
	
	BinaryTreeNode* findPredeNode(BinaryTreeNode *n)
	{
		BinaryTreeNode *p = NULL;
		if (n->left)
			return findMaxNode(n->left);
		p = n->parent;
		while (p && n == p->left)
		{
			n = p;
			p = p->parent;
		}
		return p;
	}
	
	BinaryTreeNode* findSucNode(BinaryTreeNode *n)
	{
		BinaryTreeNode *p = NULL;
		if (n->right)
			return findMinNode(n->right);
		p = n->parent;
		while (p && n == p->right)
		{
			n = p;
			p = p->parent;
		}
		return p;
	}
	
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
	
	void insertNode(Comparable d, BinaryTreeNode *n)
	{
		if (d < n->data)
		{
			if (n->left)
				insertNode(d, n->left);
			else
			{
				n->left = new BinaryTreeNode(d);
				n->left->parent = n;
			}
			n->left->height = maxHeight(n->left);
			if (height(n->left) - height(n->right) == 2)
			{
				if (d < n->left->data)
					rotateWithLeftChild(n);
				else
					doubleRotateWithLeftChild(n);
			}
		}
		else if (d > n->data)
		{
			if (n->right)
				insertNode(d, n->right);
			else
			{
				n->right = new BinaryTreeNode(d);
				n->right->parent = n;
			}
			n->right->height = maxHeight(n->right);
			if (height(n->right) - height(n->left) == 2)
			{
				if (d > n->right->data)
					rotateWithRightChild(n);
				else
					doubleRotateWithRightChild(n);
			}
		}
		else
			;
	}
	
	void removeNode(BinaryTreeNode *n)
	{
		if (!n)
			return;
		if (n->left && n->right)
		{
			//n->data = findPredeNode(n)->data;
			//removeNode(findPredeNode(n));
			n->data = findSucNode(n)->data;
			removeNode(findSucNode(n));
		}
		else
		{
			BinaryTreeNode *x = (n->left) ? n->left : n->right;
			if (n == root)
				root = x;
			else
			{
				BinaryTreeNode *p = n->parent;

				if (n == p->left)
					p->left = x;
				else
					p->right = x;

				delete n;
				n = NULL;
				if (x)
					x->parent = p;
				decreaseHeight(p);
			}
		}
	}
	
	void printTree(BinaryTreeNode *r)
	{
		if (!r)
			return;
		printTree(r->left);
		cout << r->data << "(" << r->height << ")" << " ";
		printTree(r->right);
	}
	
	int height(BinaryTreeNode *n)
	{
		return n ? n->height : -1;
	}
	
	int maxHeight(BinaryTreeNode *n)
	{
		int lh = height(n->left);
		int rh = height(n->right);
		return lh > rh ? lh+1 : rh+1;
	}
	
	void decreaseHeight(BinaryTreeNode *n)
	{
		if (n)
		{
			n->height = maxHeight(n);
			
			if ((height(n->left) - height(n->right)) == 2 )
			{
				if (height(n->left->right) > height(n->left->left))
					doubleRotateWithLeftChild(n);
				else
					rotateWithLeftChild(n);
			}
			else if ((height(n->right) - height(n->left)) == 2)
			{
				if (height(n->right->left) > height(n->right->right))
					doubleRotateWithRightChild(n);
				else
					rotateWithRightChild(n);
			}
			else
				;
			
			decreaseHeight(n->parent);
		}
	}
	
	void rotateWithLeftChild(BinaryTreeNode *k2)
	{
		BinaryTreeNode *k1 = k2->left;
		if (k1->right)
			k1->right->parent = k2;
		k2->left = k1->right;
		k1->parent = k2->parent;
		if (!k2->parent)
			root = k1;
		else if (k2 == k2->parent->left)
			k2->parent->left = k1;
		else if (k2 == k2->parent->right)
			k2->parent->right = k1;
		else
			;
		k2->parent = k1;
		k1->right = k2;
		k1->height = maxHeight(k1);
		k2->height = maxHeight(k2);
	}
	
	void rotateWithRightChild(BinaryTreeNode *k1)
	{
		BinaryTreeNode *k2 = k1->right;
		if (k2->left)
			k2->left->parent = k1;
		k1->right = k2->left;
		k2->parent = k1->parent;
		if (!k1->parent)
			root = k2;
		else if (k1 == k1->parent->left)
			k1->parent->left = k2;
		else if (k2 == k2->parent->right)
			k1->parent->right = k2;
		else
			;
		k1->parent = k2;
		k2->left = k1;
		k1->height = maxHeight(k1);
		k2->height = maxHeight(k2);
	}
	
	void doubleRotateWithLeftChild(BinaryTreeNode *k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	
	void doubleRotateWithRightChild(BinaryTreeNode *k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
};
