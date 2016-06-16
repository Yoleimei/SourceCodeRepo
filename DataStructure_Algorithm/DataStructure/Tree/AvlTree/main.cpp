#include "AvlTree.hpp"

int main() {
	AvlTree<int> *tree = new AvlTree<int>();
	tree->insert(3);
	tree->printTree();
}