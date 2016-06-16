#include <iostream>

using namespace std;

class BinarySearchTree
{
	struct BinarySearchTreeNode
	{
		int data;
		BinarySearchTreeNode* left;
		BinarySearchTreeNode* right;
		BinarySearchTreeNode* parent;
		
		BinarySearchTreeNode(int d): data(d)
		{
			left = NULL;
			right = NULL;
			parent = NULL;
		}
	}
	
	public BinarySearchTreeNode* root;
	
	public BinarySearchTreeNode* TreeSearch(BinarySearchTreeNode* x, int data)
	{
		if (x == NULL || x->data == data)
			return x;
		if (data < x->data)
			TreeSearch(x->left);
		else
			TreeSearch(x->right);
	}
	
	public BinarySearchTreeNode* TreeMinimum(BinarySearchTreeNode* x)
	{
		while (x->left != NULL)
			x = x->left;
		return x;
	}
	
	public BinarySearchTreeNode* TreeMaximum(BinarySearchTreeNode* x)
	{
		while (x->right != NULL)
			x = x->right;
		return x;
	}
	
	public BinarySearchTreeNode* TreePredecessor(BinarySearchTreeNode* x)
	{
		if (x->left != NULL)
			return TreeMaximum(x->left);
		BinarySearchTreeNode* y = x->parent;
		while (y != NULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
	
	public BinarySearchTreeNode* TreeSuccessor(BinarySearchTreeNode* x)
	{
		if (x->right != NULL)
			return TreeMinimum(x->right);
		BinarySearchTreeNode* y->x->parent;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
	
	public void TreeInsert(BinarySearchTreeNode* z)
	{
		BinarySearchTreeNode* y = NULL;
		BinarySearchTreeNode* x = root;
		while (x != NULL)
		{
			y = x;
			if (z->data < x->data)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (z->data < y->data)
			y->left = z;
		else
			y->right = z;
	}
	
	public BinarySearchTreeNode* TreeDelete(BinarySearchTreeNode* z)
	{
		if (z->left == NULL || z->right == NULL)
			y = z;
		else
			y = TreeSuccessor(z);
		if (y->left != NULL)
			x = y->left;
		else
			x = y->right;
		if (x != NULL)
			x->parent = y->parent;
		if (y->parent == NULL)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		if (y != z)
			z->data = y->data;
		return y;
	}
}