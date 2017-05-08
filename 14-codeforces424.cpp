//http://codeforces.com/problemset/problem/424/B
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <algorithm>

#define tiii tuple<int, int, int>
#define viii vector<tuple<int, int, int> >

using namespace std;

const int e6 = 1000000;
viii p;

bool option(tiii &t1, tiii &t2) {
	int x1, y1, x2, y2;
	x1 = get<0>(t1);
	y1 = get<1>(t1);
	x2 = get<0>(t2);
	y2 = get<1>(t2);
	return x1*x1 + y1*y1 < x2*x2 + y2*y2;
}

int sumElements(int num) {
	int sum = 0;
	for (int i = 0; i < num; ++i) {
		sum += get<2>(p[i]);
	}
	return sum;
}

int bs(int l, int r, int s) {
	int left, mid, right;
	int sum;

	left = l;
	right = r;
	while (left <= right) {
		mid = (left + right) / 2;
		sum = sumElements(mid);
		if (s + sum < e6) {
			left = mid + 1;
		}
		else if (s + sum > e6) {
			right = mid - 1;
		}
		else {
			return mid;
		}
	}
	return left;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("stdin.inp", "r", stdin);

	int n, s, x, y, k;
	int res;

	cin >> n >> s;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y >> k;
		p.push_back(tiii(x, y, k));
	}
	sort(p.begin(), p.end(), option);

	res = bs(0, n, s);
	if (res == n + 1) {
		cout << -1;
	}
	else if (res == 0) {
		cout << 0;
	}
	else {
		x = get<0>(p[res - 1]);
		y = get<1>(p[res - 1]);
		cout << fixed << setprecision(7) << sqrt(x*x + y*y);
	}
	return 0;
}