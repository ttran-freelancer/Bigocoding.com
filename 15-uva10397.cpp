//https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1338
// TÓM TẮT Ý TƯỞNG:
// Loại: Tìm cây khung nhỏ nhất MST -> Prim hoặc Kruskal. 
//			Bài này sử dụng Kruskal vì đã có những cạnh khung có sẵn.
// Phân tích: Đề bài yêu cầu tìm cây khung nhỏ nhất từ những cạnh khung có sẵn. 
//				Tính tổng độ dài các cạnh khung mới thêm vào.
// Giải pháp: Dùng Kruskal tìm phần còn lại của cây khung. Trả về kết quả.
// Lưu ý: res: double thay vì float
// Độ phức tạp: V + VlogV + ElogV + ElogV ~ max(VlogV, ElogV)
//		- Input: V + VlogV + ElogV
//		- Kruskal: ElogV
// Prim với khởi tạo các cạnh có sẵn = 0
#include <iostream>
#include <algorithm>
#include <cmath> // sqrt
#include <tuple>
#include <queue>
#include <vector>
#include <functional>
#include <iomanip> // setprecision, fixed

#define pii pair<int, int> 
#define tfii tuple<float, int, int>
#define pqtfii priority_queue<tfii, vector<tfii >, greater<tfii > >
#define sqr(x) (x)*(x)

using namespace std;

const int MAX = 752;

pii vertex[MAX];
int flag[MAX];
pqtfii pq;

int myabs(int x) {
	return x >= 0 ? x : -x;
}

float distance(int u, int v) {
	int h, w;
	h = myabs(vertex[u].first - vertex[v].first);
	w = myabs(vertex[u].second - vertex[v].second);
	return sqrt(sqr(h) + sqr(w));
}

void Kruskal(double &res, int n) {
	int u, v;
	float w;
	int fa, fb, tmp;

	while (!pq.empty()) {
		w = get<0>(pq.top());
		u = get<1>(pq.top());
		v = get<2>(pq.top());
		pq.pop();
		if (flag[u] != flag[v]) {
			res += w;
			fa = flag[u];
			fb = flag[v];
			tmp = min(fa, fb);
			for (int i = 1; i <= n; ++i) {
				if (flag[i] == fa || flag[i] == fb) {
					flag[i] = tmp;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("stdin.inp", "r", stdin);

	int n, m;
	int x, y, u, v;
	int fa, fb, tmp;
	float w;
	double res;

	while (cin >> n) {
		res = 0.0;

		for (int i = 1; i <= n; ++i) {
			cin >> x >> y;
			vertex[i] = pii(x, y);
			flag[i] = i;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				w = distance(i, j);
				pq.push(tfii(w, i, j));
			}
		}
		cin >> m;
		while (m--) {
			cin >> u >> v;
			if (flag[u] != flag[v]) {
				fa = flag[u];
				fb = flag[v];
				// Lưu lại nhãn ban đầu của đỉnh u, v. Tránh trường hợp bị thay đổi khi gán nhãn mới.
				tmp = min(fa, fb);
				// Tìm nhãn nhỏ nhất của u, v. Gán lại cho tất cả các đỉnh có nhãn bằng u, v.
				for (int i = 1; i <= n; ++i) {
					if (flag[i] == fa || flag[i] == fb) {
						flag[i] = tmp;
					}
				}
			}
		}
		Kruskal(res, n);

		cout << fixed << setprecision(2) << res << endl;
	}

	return 0;
}