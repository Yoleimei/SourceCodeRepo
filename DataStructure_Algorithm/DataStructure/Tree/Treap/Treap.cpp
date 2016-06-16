#include <iostream>
#include <queue>

using namespace std;

struct Treap {
public:
	Treap() { root = NULL; }

	void insert(int elem, int prio) {
		insert(elem, prio, root);
	}
	void remove(int elem) {
		remove(elem, root);
	}
	bool empty() {
		return (root == NULL) ? true : false;
	}
	bool contain(int elem) {

	}
	void levelTraversal() {
		if (root == NULL)
			return;
		queue<TreapNode> nodes;
		nodes.push(*root);
		while (!nodes.empty()) {
			TreapNode n = nodes.front();
			nodes.pop();
			cout << n << endl;
			if (n.left) {
				cout << n << "的左子节点是" << *(n.left) << endl;
				nodes.push(*(n.left));
			}
			if (n.right) {
				cout << n << "的右子节点是" << *(n.right) << endl;
				nodes.push(*(n.right));
			}
		}
	}

private:
	struct TreapNode {
		int elem;
		int prio;
		TreapNode *left;
		TreapNode *right;

		TreapNode(int e, int p, TreapNode *l = NULL, TreapNode *r = NULL) : elem(e), prio(p), left(l), right(r){}

		friend ostream& operator << (ostream& out, const TreapNode& node) {
			out << '(' << node.elem << ',' << node.prio << ')';
			return out;
		}
	};

	TreapNode *root;

	void leftRotate(TreapNode*& k1) {
		TreapNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1 = k2;
	}

	void rightRotate(TreapNode*& k2) {
		TreapNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2 = k1;
	}

	void insert(int elem, int prio, TreapNode*& node) {
		if (node == NULL)
			node = new TreapNode(elem, prio);
		else if (elem < node->elem) {
			insert(elem, prio, node->left);
			if (node->left->prio > node->prio)
				rightRotate(node);
		}
		else if (elem > node->elem) {
			insert(elem, prio, node->right);
			if (node->right->prio > node->prio)
				leftRotate(node);
		}
		else;
	}

	void remove(int elem, TreapNode*& node) {
		if (node == NULL)
			return;
		if (elem < node->elem)
			remove(elem, node->left);
		else if (elem > node->elem)
			remove(elem, node->right);
		else {
			if (!node->left && !node->right){
				delete node;
				node = NULL;
			}
			else if (!node->left) {
				TreapNode *tmp = node->right;
				delete node;
				node = tmp;
			}
			else if (!node->right) {
				TreapNode *tmp = node->left;
				delete node;
				node = tmp;
			}
			else {
				if (node->left->prio > node->right->prio)
					rightRotate(node);
				else
					leftRotate(node);
				remove(elem, node);
			}
		}
	}

	TreapNode find(int elem) {

	}
};

int main() {
	Treap *treap = new Treap();
	treap->insert(2, 10);
	treap->insert(4, 3);
	treap->insert(5, 8);
	treap->insert(1, 5);
	treap->insert(0, 2);
	treap->insert(9, 1);
	treap->levelTraversal();
	int elem;
	while (!treap->empty()) {
		cout << "请输入要删除的元素:";
		cin >> elem;
		treap->remove(elem);
		treap->levelTraversal();
	}
	delete treap;
	system("pause");
}