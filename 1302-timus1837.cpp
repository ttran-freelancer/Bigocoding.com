http://acm.timus.ru/problem.aspx?space=1&num=1837



#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int INF = 1000000009;
stringstream ss;
map<string, int> mp;
vector<pair<int, int> > graph;
vector<int> team;
vector<int> dist(302, INF);

void BellmanFord(int n) {
	int f, s;
	dist[mp["Isenbaev"]] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < graph.size(); ++j) {
			f = graph[j].first;
			s = graph[j].second;
			if (dist[s] > dist[f] + 1) {
				dist[s] = dist[f] + 1;
			}
			if (dist[f] > dist[s] + 1) {
				dist[f] = dist[s] + 1;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	//freopen("stdin.inp", "r", stdin);

	int n;
	string line, name;
	int k = 0;

	cin >> n;
	getline(cin, line);
	while (n--) {
		ss.clear();
		team.clear();

		getline(cin, line);
		ss << line;
		while (ss >> name) {
			if (mp.find(name) == mp.end()) {
				mp[name] = k++;
			}
			team.push_back(mp[name]);
		}
		for (int i = 0; i < team.size(); ++i) {
			for (int j = i + 1; j < team.size(); ++j) {
				graph.push_back(pair<int, int>(team[i], team[j]));
			}
		}
	}

	if (mp.find("Isenbaev") != mp.end()) {
		BellmanFord(302);
	}

	for (map<string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
		cout << it->first << " ";
		if (dist[it->second] == 1000000009) {
			cout << "undefined";
		}
		else {
			cout << dist[it->second];
		}
		cout << endl;
	}

	return 0;
}