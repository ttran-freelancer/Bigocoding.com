http://acm.timus.ru/problem.aspx?space=1&num=1196



#include <iostream>
#include <map>

using namespace std;

map<int, int> mp;

int main() {
	ios_base::sync_with_stdio(false);
	//freopen("stdin.inp", "r", stdin);

	int n, m;
	int val, res = 0;

	cin >> n;
	while (n--) {
		cin >> val;
		mp[val] = 0;
	}
	cin >> m;
	while (m--) {
		cin >> val;
		if (mp.find(val) != mp.end()) {
			++mp[val];
		}
	}
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
		res += it->second;
	}
	cout << res;
	return 0;
}