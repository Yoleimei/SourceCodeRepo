#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

// �����������
// 1 ÿ���ڵ�Ҫô�Ǻ�ģ�Ҫô�Ǻڵ�
// 2 ���ڵ��Ǻڵ�
// 3 ���һ���ڵ��Ǻ�ģ��������������Ӷ��Ǻڵ�
// 4 ��ÿ���ڵ㣬�Ӹýڵ㵽������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ�
class RedBlackTree {
public:
	RedBlackTree() { 
		nil = new TreeNode(-1); 
		nil->parent = nil; 
		nil->left = nil;
		nil->right = nil;
		nil->color = BLACK;
		root = nil; 
	}
	~RedBlackTree() { clear(root); delete nil; }
	void insert(int elem) {
		rb_insert(new TreeNode(elem, nil, nil, nil));
	}
	void remove(int elem) {
		TreeNode *node = find(elem, root);
		if (node != nil)
			rb_remove(node);
	}
	void print() {
		InOrderTraversal(root);
		cout << endl;
	}
	bool empty() {
		return (root == nil) ? true : false;
	}
private:
	enum Color { RED, BLACK };
	struct TreeNode {
		int elem;
		Color color;
		TreeNode *parent;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int e, TreeNode *p = NULL, TreeNode *l = NULL, TreeNode *r = NULL, Color c = RED) : elem(e), color(c), parent(p), left(l), right(r) {}
	};
	TreeNode *nil;
	TreeNode *root;
	TreeNode* find(int elem, TreeNode* node) {
		if (node == nil)
			return nil;
		if (elem == node->elem)
			return node;
		else if (elem < node->elem)
			return find(elem, node->left);
		else if (elem > node->elem)
			return find(elem, node->right);
		else;

	}
	void leftRotate(TreeNode* k1) {
		// set k2
		TreeNode *k2 = k1->right;
		// turn k2's left subtree into k1's right subtree
		k1->right = k2->left;
		k2->left->parent = k1;
		// link k1's parent to k2
		k2->parent = k1->parent;
		if (k2->parent == nil) 
			root = k2;
		else if (k1 = k2->parent->left)
			k2->parent->left = k2;
		else
			k2->parent->right = k2;
		// put k1 on k2's left
		k2->left = k1;
		k1->parent = k2;
	}
	void rightRotate(TreeNode* k2) {
		// set k1
		TreeNode *k1 = k2->left;
		// turn k1's right subtree into k2's left subtree
		k2->left = k1->right;
		k1->right->parent = k2;
		// link k2's parent to k1
		k1->parent = k2->parent;
		if (k1->parent == nil)
			root = k1;
		else if (k2 = k1->parent->left)
			k1->parent->left = k1;
		else
			k1->parent->right = k1;
		// put k2 on k1's right
		k1->right = k2;
		k2->parent = k1;
	}
	void rb_insert(TreeNode *z) {
		TreeNode *y = nil;
		TreeNode *x = root;
		// find the last leaf node
		while (x != nil) {
			y = x;
			if (z->elem < x->elem)
				x = x->left;
			else
				x = x->right;
		}
		// link z to y as its parent
		z->parent = y;
		if (y == nil)
			root = z;
		else if (z->elem < y->elem)
			y->left = z;
		else
			y->right = z;
		// initialize z with RED color
		z->left = nil;
		z->right = nil;
		z->color = RED; // ���ܻ��ƻ�����2������3���������ƻ�����4
		rb_insert_fixup(z);
		print();
	}
	void rb_insert_fixup(TreeNode *z) {
		TreeNode *y;
		while (z->parent->parent != nil && z->parent->color == RED) { // ���´�����������3
			// ���1��z�ĸ��ڵ������ӽڵ㣬z���常�ڵ���Ϊz���ڵ�ĸ��ڵ�����ӽڵ�
			if (z->parent == z->parent->parent->left) {
				// y��z���常�ڵ�
				y = z->parent->parent->right;
				// Case 1: z���常�ڵ��Ǻ��
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				// Case 2: z���常�ڵ��Ǻڵģ�����z�����ӽڵ�
				else if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);
				}
				// Case 3:z���常�ڵ��Ǻ�ɫ������z�����ӽڵ�
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			// ���2��z�ĸ��ڵ������ӽڵ㣬z���常�ڵ���Ϊz���ڵ�ĸ��ڵ�����ӽڵ�
			else {
				// y��z���常�ڵ�
				y = z->parent->parent->left;
				// Case 1: z���常�ڵ��Ǻ��
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				// Case 2: z���常�ڵ��Ǻڵģ�����z�����ӽڵ�
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				// Case 3: z���常�ڵ��Ǻڵģ�����z�����ӽڵ�
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK; // ��������2
	}
	TreeNode* findSuccessor(TreeNode *z) {
		if (z->right != nil) {
			z = z->right;
			while (z->left != nil)
				z = z->left;
			return z;
		}
		TreeNode *p = z->parent;
		while (p != nil && z == p->right) {
			z = p;
			p = p->parent;
		}
		return p;
	}
	void rb_remove(TreeNode *z) {
		TreeNode *x, *y;
		// y�������ļ�����remove�Ľڵ�
		if (z->left == nil || z->right == nil)
			y = z;
		else
			y = findSuccessor(z); // y�϶�û�����ӽڵ�
		// x��y���ӽڵ�
		if (y->left != nil)
			x = y->left;
		else
			x = y->right;
		// x�ĸ��ڵ�ָ��y�ĸ��ڵ㣬����x�ǲ���nil
		x->parent = y->parent;
		if (y->parent == nil)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		if (y != z)
			z->elem = y->elem;
		// �����ɾ�Ľڵ��Ǻ�ɫ�ģ���������������
		// 1 ���yԭ���Ǹ��ڵ㣬��y��һ����ɫ���ӽڵ��Ϊ���µĸ�����Υ��������2
		// 2 ���x��y->parent���Ǻ�ɫ�ģ���Υ��������3
		// 3 ɾ��y��������ǰ����y���κ�·���Ϻڽڵ������1��Υ��������4
		if (y->color == BLACK)
			rb_remove_fixup(x); 
		delete y;
		y = NULL;
	}
	void rb_remove_fixup(TreeNode *x) {
		TreeNode *w;
		if (x == nil)
			return;
		// ��ΪΥ��������4���ʼٶ�x�������һ�غ�ɫ������������4
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				// x�����ӽڵ㣬w��x���ֵܽڵ�
				w = x->parent->right;
				// Case 1: x���ֵܽڵ�w�Ǻ�ɫ�ģ���ʱw���ӽڵ㶼�Ǻ�ɫ�ģ�ͨ����ת����ת��ΪCase234
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				// Case 2: x���ֵܽڵ�w�Ǻ�ɫ�ģ�����w���������Ӷ��Ǻ�ɫ��
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED; // ��x��x���ֵܽڵ�wȥ��һ�غ�ɫ
					x = x->parent; // �����˱�������4���������ϲ�����
				}
				// Case 3: x���ֵܽڵ�w�Ǻ�ɫ�ģ�w�����ӽڵ��Ǻ�ɫ�ģ����ӽڵ��Ǻ�ɫ�ģ�ͨ����ת����ת��ΪCase4
				else if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				// Case 4: x���ֵܽڵ�w�Ǻ�ɫ�ģ�w�����ӽڵ��Ǻ�ɫ��
				else {// ����Ҫ��һ�������
					w->color = x->parent->color;
					x->parent->color = BLACK; // ������Ϊx�����һ�غ�ɫ������������4������3
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				// x�����ӽڵ㣬w��x���ֵܽڵ�
				w = x->parent->left;
				// Case 1: x���ֵܽڵ�w�Ǻ�ɫ�ģ���ʱw���ӽڵ㶼�Ǻ�ɫ�ģ�ͨ����ת����ת��ΪCase234
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				// Case 2: x���ֵܽڵ�w�Ǻ�ɫ�ģ�����w���������Ӷ��Ǻ�ɫ��
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				// Case 3: x���ֵܽڵ�w�Ǻ�ɫ�ģ�w�����ӽڵ��Ǻ�ɫ�ģ����ӽڵ��Ǻ�ɫ�ģ�ͨ����ת����ת��ΪCase4
				else if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = x->parent->left;
				}
				// Case 4: x���ֵܽڵ�w�Ǻ�ɫ�ģ�w�����ӽڵ��Ǻ�ɫ��
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK; // ����������2
	}
	void InOrderTraversal(TreeNode *node) {
		if (node == nil)
			return;
		InOrderTraversal(node->left);
		cout << setw(3) << node->elem << '(' << node->color << ')';
		InOrderTraversal(node->right);
	}
	void clear(TreeNode *node) {
		if (node == nil)
			return;
		if (node->left != nil)
			clear(node->left);
		if (node->right != nil)
			clear(node->right);
		delete node;
		node = NULL;
	}
};

int main() {
	static default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 99);
	
	RedBlackTree *tree = new RedBlackTree();
	for (int i = 0; i < 10; ++i) {
		int elem = distribution(generator);
		cout << setw(3) << elem << endl;
		tree->insert(elem);
	}
	while (!tree->empty()) {
		int elem;
		cout << "������Ҫɾ������: " << endl;
		cin >> elem;
		tree->remove(elem);
		tree->print();
	}

	delete tree;
	tree = NULL;
	system("pause");
}
