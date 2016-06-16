#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

// 红黑树的性质
// 1 每个节点要么是红的，要么是黑的
// 2 根节点是黑的
// 3 如果一个节点是红的，则它的两个儿子都是黑的
// 4 对每个节点，从该节点到其子孙节点的所有路径上包含相同数目的黑节点
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
		z->color = RED; // 可能会破坏性质2或性质3，但不会破坏性质4
		rb_insert_fixup(z);
		print();
	}
	void rb_insert_fixup(TreeNode *z) {
		TreeNode *y;
		while (z->parent->parent != nil && z->parent->color == RED) { // 以下代码修正性质3
			// 情况1：z的父节点是左子节点，z的叔父节点则为z父节点的父节点的右子节点
			if (z->parent == z->parent->parent->left) {
				// y是z的叔父节点
				y = z->parent->parent->right;
				// Case 1: z的叔父节点是红的
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				// Case 2: z的叔父节点是黑的，而且z是右子节点
				else if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);
				}
				// Case 3:z的叔父节点是黑色，而且z是左子节点
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			// 情况2：z的父节点是右子节点，z的叔父节点则为z父节点的父节点的左子节点
			else {
				// y是z的叔父节点
				y = z->parent->parent->left;
				// Case 1: z的叔父节点是红的
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				// Case 2: z的叔父节点是黑的，而且z是左子节点
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				// Case 3: z的叔父节点是黑的，而且z是右子节点
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK; // 修正性质2
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
		// y是真正的即将被remove的节点
		if (z->left == nil || z->right == nil)
			y = z;
		else
			y = findSuccessor(z); // y肯定没有左子节点
		// x是y的子节点
		if (y->left != nil)
			x = y->left;
		else
			x = y->right;
		// x的父节点指向y的父节点，不管x是不是nil
		x->parent = y->parent;
		if (y->parent == nil)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		if (y != z)
			z->elem = y->elem;
		// 如果被删的节点是黑色的，则会产生三个问题
		// 1 如果y原来是根节点，而y的一个红色的子节点称为了新的根，则违反了性质2
		// 2 如果x和y->parent都是红色的，则违反了性质3
		// 3 删除y将导致先前包含y的任何路径上黑节点个数少1，违反了性质4
		if (y->color == BLACK)
			rb_remove_fixup(x); 
		delete y;
		y = NULL;
	}
	void rb_remove_fixup(TreeNode *x) {
		TreeNode *w;
		if (x == nil)
			return;
		// 因为违反了性质4，故假定x上添加了一重黑色用以修正性质4
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				// x是左子节点，w是x的兄弟节点
				w = x->parent->right;
				// Case 1: x的兄弟节点w是红色的，此时w的子节点都是黑色的，通过旋转操作转化为Case234
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				// Case 2: x的兄弟节点w是黑色的，而且w的两个孩子都是黑色的
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED; // 将x和x的兄弟节点w去掉一重黑色
					x = x->parent; // 修正了本层性质4，继续向上层修正
				}
				// Case 3: x的兄弟节点w是黑色的，w的左子节点是红色的，右子节点是黑色的，通过旋转操作转化为Case4
				else if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				// Case 4: x的兄弟节点w是黑色的，w的右子节点是红色的
				else {// 最重要的一种情况，
					w->color = x->parent->color;
					x->parent->color = BLACK; // 左旋后为x添加了一重黑色，修正了性质4和性质3
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				// x是右子节点，w是x的兄弟节点
				w = x->parent->left;
				// Case 1: x的兄弟节点w是红色的，此时w的子节点都是黑色的，通过旋转操作转化为Case234
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				// Case 2: x的兄弟节点w是黑色的，而且w的两个孩子都是黑色的
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				// Case 3: x的兄弟节点w是黑色的，w的右子节点是红色的，左子节点是黑色的，通过旋转操作转化为Case4
				else if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = x->parent->left;
				}
				// Case 4: x的兄弟节点w是黑色的，w的左子节点是红色的
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK; // 修正了性质2
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
		cout << "请输入要删除的数: " << endl;
		cin >> elem;
		tree->remove(elem);
		tree->print();
	}

	delete tree;
	tree = NULL;
	system("pause");
}
