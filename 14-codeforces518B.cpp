//http://codeforces.com/problemset/problem/518/B

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char, int> mp;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	freopen("stdin.inp", "r", stdin);

	string msg, news, remain;
	int c1, c2;
	char ch;

	cin >> msg;
	for (int i = 0; i < msg.length(); ++i) {
		++mp[msg[i]];
	}

	cin >> news;
	c1 = 0;
	c2 = 0;
	for (int j = 0; j < news.length(); ++j) {
		ch = news[j];
		if (mp[ch]) {
			--mp[ch];
			++c1;
			continue;
		}
		remain += ch;
	}
	for (int j = 0; j < remain.length(); ++j) {
		if (remain[j] >= 'a' && remain[j] <= 'z') {
			ch = remain[j] - 'a' + 'A';
		}
		else {
			ch = remain[j] - 'A' + 'a';
		}
		if (mp[ch]) {
			--mp[ch];
			++c2;
		}
	}
	cout << c1 << " " << c2;
	return 0;
}