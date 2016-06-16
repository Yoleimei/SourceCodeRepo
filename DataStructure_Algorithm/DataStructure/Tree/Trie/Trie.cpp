#include <iostream>
#include <string>

using namespace std;

struct Trie {
public:
	Trie() { root = new TrieNode(""); }
	~Trie() { delete root; }

	void createTrie(string strKey, string strValue) {
		TrieNode *node = root;
		TrieNode *pre = root;
		for (auto it = strKey.begin(); it != strKey.end(); ++it) {
			pre = node;
			int idx;
			if (isalpha(*it))
				idx = *it - 'a';
			else if (isdigit(*it))
				idx = *it - '0' + 26;
			else
				idx = 36;
			if (node->children[idx] == NULL)
				node->children[idx] = new TrieNode("");
			node = node->children[idx];
		}
		pre->str = strValue;
	}

	string findTrie(string str) {
		TrieNode *node = root;
		TrieNode *pre = root;
		for (auto it = str.begin(); it != str.end(); ++it) {
			pre = node;
			int idx;
			if (isalpha(*it))
				idx = *it - 'a';
			else if (isdigit(*it))
				idx = *it - '0' + 26;
			else
				idx = 36;
			if (node->children[idx] == NULL)
				return "noting";
			node = node->children[idx];
		}
		return pre->str;
	}

private:
	struct TrieNode {
		string str;
		TrieNode *children[37];

		TrieNode(string s) : str(s) { 
			for (int i = 0; i < 37; ++i) children[i] = NULL;
		}
	};

	TrieNode *root;
};

int main() {
	Trie *trie = new Trie();
	trie->createTrie("127.0.0.1", "localhost");
	trie->createTrie("192.168.0.1", "gateway");
	trie->createTrie("218.2.135.1", "DNS Server");
	cout << trie->findTrie("127.0.0.1") << endl;
	cout << trie->findTrie("192.168.0.1") << endl;
	cout << trie->findTrie("218.2.135.1") << endl;
	cout << trie->findTrie("baidu") << endl;

	delete trie;
	system("pause");
}