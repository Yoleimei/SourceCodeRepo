#include <iostream>

using namespace std;

class RedBlackTree
{
public:
	RedBlackTree() 
	{ 
		nil = new BinaryTreeNode(-1, BLACK); 
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil; 
	}
	~RedBlackTree() { makeEmpty(); }
	
	bool isEmpty()
	{
		return root == nil ? true : false;
	}

	void makeEmpty()
	{
		makeEmpty(root);
	}

	void insert(int d)
	{
		BinaryTreeNode *r = root;
		BinaryTreeNode *p = nil;
		
		while (r != nil)
		{
			p = r;
			if (d < r->data)
				r = r->left;
			else if (d > r->data)
				r = r->right;
			else
				return; //��������ͬ�򲻲���
		}
		r = new BinaryTreeNode(d, RED, nil, nil, nil);
		if (p == nil)
			root = r;
		else if (d < p->data)
			p->left = r;
		else
			p->right = r;
		r->parent = p;

		insertFixup(r);
	}
	
	void remove(int d)
	{
		BinaryTreeNode *x = nil;
		BinaryTreeNode *y = searchNode(d);
		
		if (y != nil)
		{
			while (y->left != nil && y->right != nil)
			{
				y->data = findSucNode(y)->data;
				y = findSucNode(y);
			}
			x = (y->left != nil) ? y->left : y->right;
			x->parent = y->parent;

			if (y->parent == nil)
				root = x;
			else
			{
				if (y == y->parent->left)
					y->parent->left = x;
				else
					y->parent->right = x;
			}
			if (y->color == BLACK)
				removeFixup(x);
			delete y;
		}
	}
	
	void printTree()
	{
		if (root != nil)
		{
			printTree(root);
			cout << endl;
		}
		else
			cout << "����û������" << endl;
	}

private:
	enum RedBlack
	{
		RED,
		BLACK
	};
	struct BinaryTreeNode
	{
		int data;
		RedBlack color;
		BinaryTreeNode *left;
		BinaryTreeNode *right;
		BinaryTreeNode *parent;
		
		BinaryTreeNode(int d, RedBlack c, BinaryTreeNode *l=NULL, BinaryTreeNode *r=NULL, BinaryTreeNode *p=NULL): data(d), color(c), left(l), right(r), parent(p) { }
	};

	BinaryTreeNode *root;
	BinaryTreeNode *nil;
	
	BinaryTreeNode* findMinNode(BinaryTreeNode *n)
	{
		if (n->left != nil)
			return findMinNode(n->left);
		return n;
	}

	BinaryTreeNode* findSucNode(BinaryTreeNode *n)
	{
		BinaryTreeNode *p = nil;
		if (n->right != nil)
			return findMinNode(n->right);
		p = n->parent;
		while (p != nil && n == p->right)
		{
			n = p;
			p = p->parent;
		}
		return p;
	}

	BinaryTreeNode* searchNode(int d)
	{
		BinaryTreeNode *r = root;
		while (r != nil)
		{
			if (d < r->data)
				r = r->left;
			else if (d > r->data)
				r = r->right;
			else
				return r;
		}
		return nil;
	}
	
	void makeEmpty(BinaryTreeNode *&n) // ��Ҫ�ı�ָ�����
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
	
	void leftRotate(BinaryTreeNode *k1)
	{
		BinaryTreeNode *k2 = k1->right;
		if (k2->left)
			k2->left->parent = k1;
		k1->right = k2->left;
		k2->parent = k1->parent;
		if (k1->parent == nil)
			root = k2;
		else if (k1 == k1->parent->left)
			k1->parent->left = k2;
		else if (k2 == k2->parent->right)
			k1->parent->right = k2;
		else
			;
		k1->parent = k2;
		k2->left = k1;
	}
	
	void rightRotate(BinaryTreeNode *k2)
	{
		BinaryTreeNode *k1 = k2->left;
		if (k1->right)
			k1->right->parent = k2;
		k2->left = k1->right;
		k1->parent = k2->parent;
		if (k2->parent == nil)
			root = k1;
		else if (k2 == k2->parent->left)
			k2->parent->left = k1;
		else if (k2 == k2->parent->right)
			k2->parent->right = k1;
		else
			;
		k2->parent = k1;
		k1->right = k2;
	}
	
	void insertFixup(BinaryTreeNode *z)
	{
		BinaryTreeNode *y = nil;
		while (z->parent->parent != nil && z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left) // z�ĸ��ڵ������ӽڵ�
			{
				y = z->parent->parent->right; //��ȡz���常�ڵ�
		
				if (y->color == RED) // ���1���常�ڵ�y�Ǻ�ɫ
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) // ���2���常�ڵ�y�Ǻ�ɫ����zΪ���ӽڵ�
				{
					z = z->parent;
					leftRotate(z);
				}
				else // ���3���常�ڵ�y�Ǻ�ɫ����zΪ���ӽڵ�
				{
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			else // z�ĸ��ڵ������ӽڵ�
			{
				y = z->parent->parent->left; //��ȡz���常�ڵ�
		
				if (y->color == RED) // ���1
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else if (z == z->parent->left) // ���2
				{
					z = z->parent;
					rightRotate(z);
				}
				else // ���3
				{
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	
	void removeFixup(BinaryTreeNode *x)
	{
		BinaryTreeNode *w = nil;
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;

				if (w == nil)
				{
					x = root;
					break;
				}

				if (w->color == RED) 
				{ // ���1��x���ֵܽڵ�wΪ��ɫ
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{ // ���2��x���ֵܽڵ�wΪ��ɫ����w���ӽڵ㶼Ϊ��ɫ
					w->color = RED;
					x = x->parent;
				}
				else if (w->right->color == BLACK)
				{ // ���3��x���ֵܽڵ�wΪ��ɫ����w������Ϊ��ɫ������Ϊ��ɫ
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				else
				{ // ���4��x���ֵܽڵ�wΪ��ɫ����w������Ϊ��ɫ������Ϊ��ɫ
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;

				if (w == nil)
				{
					x = root;
					break;
				}

				if (w->color == RED) 
				{ // ���1��x���ֵܽڵ�wΪ��ɫ
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{ // ���2��x���ֵܽڵ�wΪ��ɫ����w���ӽڵ㶼Ϊ��ɫ
					w->color = RED;
					x = x->parent;
				}
				else if (w->left->color == BLACK)
				{ // ���3��x���ֵܽڵ�wΪ��ɫ����w������Ϊ��ɫ������Ϊ��ɫ
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = x->parent->left;
				}
				else
				{ // ���4��x���ֵܽڵ�wΪ��ɫ����w������Ϊ��ɫ������Ϊ��ɫ
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
	
	void printTree(BinaryTreeNode *r)
	{
		if (r == nil)
			return;
		printTree(r->left);
		cout << r->data << "(" << r->color << ")" << " ";
		printTree(r->right);
	}
};
