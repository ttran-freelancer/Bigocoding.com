//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541
// TÓM TẮT Ý TƯỞNG
// Loại: Tìm cây khung nhỏ nhất. MST -> Prim hoặc Kruskal. Bài này sử dụng Prim.
// Phân tích: Đề bài yêu cầu tìm 2 cây khung nhỏ nhất khác nhau. Tính tổng độ dài cây khung đó.
// Giải pháp: Vì vậy sau khi tìm được cây khung nhỏ nhất. Xoá từng cạnh 1 trên cây khung nhỏ nhất đó.
//				Để tìm cây khung nhỏ nhất tiếp theo mà không bị trùng với cây khung trước. (n - 1 lần)
// Độ phức tạp: E + ElogV + EVlogV ~ EVlogV
// 		- Input: E
// 		- Prim: ElogV
// 		- Tìm cây khung nhỏ nhất thứ 2: EVlogV
#include <iostream>
#include <queue>
#include <functional>
#include <cstring>
#include <algorithm>
#include <vector>

#define pii pair<int, int>
#define pqpii priority_queue<pii, vector<pii >, greater<pii > >
#define vi vector<int>
#define vpii vector<pii >

using namespace std;

const int INF = 1000000009;
const int MAX = 102;

vpii graph[MAX];
int path[MAX];
bool visited[MAX];
vi dist;
bool edge[MAX][MAX];
int p[MAX];

int Prim(int s, int n) {
	memset(path, -1, sizeof(path));
	memset(visited, false, sizeof(visited));
	dist = vi(MAX, INF);

	pqpii pq;
	int u, v, w;
	int cost = 0;

	dist[s] = 0;
	pq.push(pii(0, s));
	while (!pq.empty()) {
		u = pq.top().second;
		pq.pop();
		visited[u] = true;
		for (int i = 0; i < graph[u].size(); ++i) {
			v = graph[u][i].first;
			w = graph[u][i].second;
			if (edge[u][v] && !visited[v] && dist[v] > w) {
				dist[v] = w;
				pq.push(pii(w, v));
				path[v] = u;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (dist[i] != INF) {
			cost += dist[i];
		}
		else {
			// Trường hợp không hình thành cây khung.
			return -1;
		}
	}
	return cost;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("stdin.inp", "r", stdin);

	int t, n, m;
	int u, v, w;
	int tmp;
	int s1, s2;

	cin >> t;
	while (t--) {
		s2 = INF;
		// Khởi tạo s2 bằng INF để so sánh
		memset(edge, true, sizeof(edge));
		for (int i = 0; i < MAX; ++i) {
			graph[i].clear();
		}

		cin >> n >> m;
		while (m--) {
			cin >> u >> v >> w;
			graph[u].push_back(pii(v, w));
			graph[v].push_back(pii(u, w));
		}
		
		// Tìm cây khung nhỏ nhất (s1)
		tmp = Prim(1, n);
		if (tmp != -1) {
			s1 = tmp;
		}
		// Lưu lại cây khung nhỏ nhất để thực hiện xoá từng cạnh
		for (int i = 0; i <= n; ++i) {
			p[i] = path[i];
		}
		
		// Tìm cây khung nhỏ thứ 2 (s2)
		for (int i = 1; i <= n; ++i) {
			if (p[i] != -1) {
				u = p[i];
				v = i;
				edge[u][v] = false;
				edge[v][u] = false;
				// edge(u, v): false đại diện cho đang xoá cạnh u, v của cây khung nhỏ nhất.
				tmp = Prim(1, n);
				if (tmp != -1) {
					s2 = min(s2, tmp);
				}
				edge[u][v] = true;
				edge[v][u] = true;
			}
		}
		
		// Kiểm tra xem có tồn tại cây khung nhỏ thứ 2 không. Mặc dù đề bài đã mặc định là tồn tại.
		if (s2 != INF) {
			cout << s1 << " " << s2 << endl;
		}
		else {
			cout << s1 << " " << s1 << endl;
		}
	}

	return 0;
}