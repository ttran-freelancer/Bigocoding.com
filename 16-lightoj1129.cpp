//http://lightoj.com/volume_showproblem.php?problem=1129
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET = 10;
const char ALPHA = '0';

struct Node {
	Node *child[ALPHABET];
	int isLeaf;
};

Node *root;
vector<string> words;

Node* newNode() {
	Node *node = new Node;
	for (int i = 0; i < ALPHABET; ++i) {
		node->child[i] = NULL;
	}
	node->isLeaf = 0;
	return node;
}

void addWord(Node *root, string word) {
	Node *node = root;
	int ch;

	if (!node) {
		node = newNode();
	}

	for (int i = 0; i < word.length(); ++i) {
		ch = word[i] - ALPHA;
		if (!node->child[ch]) {
			node->child[ch] = newNode();
		}
		node = node->child[ch];
	}
	++node->isLeaf;
}

bool isEmpty(Node *node) {
	for (int i = 0; i < ALPHABET; ++i) {
		if (node->child[i]) {
			return false;
		}
	}
	return true;
}

bool removeWord(Node *root, string word, int level) {
	int len = word.length();
	int ch = word[level];

	if (!root) {
		return false;
	}

	if (level == len) {
		--root->isLeaf;
	}
	else {
		removeWord(root->child[ch], word, level + 1);
	}

	if (!root->child[ch]->isLeaf && isEmpty(root->child[ch])) {
		delete root->child[ch];
		root->child[ch] = NULL;
		return true;
	}
	return false;
}

bool findWord(Node *root, string word) {
	Node *node = root;
	int ch;

	for (int i = 0; i < word.length(); ++i) {
		ch = word[i] - ALPHA;
		if (!node->child[ch]) {
			return false;
		}
		node = node->child[ch];
	}
	return node->isLeaf;
}

void deleteTrie(Node *root) {
	if (root) {
		for (int i = 0; i < ALPHABET; ++i) {
			deleteTrie(root->child[i]);
			root->child[i] = NULL;
		}
		delete root;
	}
}

// Hàm consitent được chỉnh sửa từ hàm findWord để thực hiện yêu cầu đề bài:
// 		- Không cần kiểm tra node->child[ch] = NULL hay không. Tại vì 'word' đã tồn tại trong 'trie'.
//		- Chỉ chạy đến word.length() - 1 thay vì chạy đến word.length(). 
// 			Vì tính tổng các 'isLeaf' bỏ qua 'isLeaf' ký tự cuối cùng. Kiểm tra xem khác 0 hay không?
int consitent(Node *root, string word) {
	Node *node = root;
	int ch;
	int res = 0;

	for (int i = 0; i < word.length() - 1; ++i) {
		ch = word[i] - ALPHA;
		res += node->child[ch]->isLeaf;
		node = node->child[ch];
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("stdin.inp", "r", stdin);

	int cnt = 0;
	int t, n;
	string number;
	bool flag;

	cin >> t;
	while (t--) {
		deleteTrie(root);
		root = new Node();
		words.clear();
		flag = false;

		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> number;
			words.push_back(number);
			addWord(root, number);
		}
		for (int i = 0; i < n; ++i) {
			if (consitent(root, words[i])) {
				flag = true;
				// flag: true, tức là tồn tại 1 'word' này là chuỗi con của 1 'word' khác -> In ra "NO".
				break;
			}
		}

		cout << "Case " << ++cnt << ": ";
		if (flag) {
			cout << "NO" << endl;
		}
		else {
			cout << "YES" << endl;
		}
	}
	return 0;
}