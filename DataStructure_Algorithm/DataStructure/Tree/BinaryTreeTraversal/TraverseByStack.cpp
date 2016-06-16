#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int data;
	Node *left;
	Node *right;

	Node(int d) : data(d), left(NULL), right(NULL) {}
	Node(const Node *n) {
		this->data = n->data;
		this->left = n->left;
		this->right = n->right;
	}
	bool equals(const Node &n) {
		return(this->data==n.data && this->left==n.left && this->right==n.right);
	}
};

void PreOrder(Node *n) {
	// ÖÐ×óÓÒ
	stack<Node*> nodeStack;
	while (n || !nodeStack.empty()) {
		while (n) {
			nodeStack.push(n);
			cout << n->data << " ";
			n = n->left;
		}
		n = nodeStack.top();
		nodeStack.pop();
		n = n->right;
	}
	cout << endl;
}

void InOrder(Node *n) {
	// ×óÖÐÓÒ
	stack<Node*> nodeStack;
	while (n || !nodeStack.empty()) {
		while (n) {
			nodeStack.push(n);
			n = n->left;
		}
		n = nodeStack.top();
		nodeStack.pop();
		cout << n->data << " ";
		n = n->right;
	}
	cout << endl;
}

void PostOrder(Node *n) {
	// ×óÓÒÖÐ
	bool visited[8];
	stack<Node*> nodeStack;
	while (n) {
		nodeStack.push(n);
		visited[nodeStack.size()] = false;
		n = n->left;
	}
	while (!nodeStack.empty()) {
		n = nodeStack.top();
		while (n->right && visited[nodeStack.size()] == false) {
			visited[nodeStack.size()] == true;
			n = n->right;
			while (n) {
				nodeStack.push(n);
				visited[nodeStack.size()] = false;
				n = n->left;
			}
			n = nodeStack.top();
		}
		n = nodeStack.top();
		nodeStack.pop();
		cout << n->data << " ";
	}
	cout << endl;
}

int main() {
	Node *root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
	PreOrder(root);
	InOrder(root);
	//PostOrder(root);  // has error
	system("pause");
}