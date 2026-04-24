#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>

using namespace std;
using ll = long long;

bool bfs(int src, int n, vector<vector<int>>& adj, vector<int>& dist, vector<int>& teams) {
    queue<int> q;

    dist[src] = 0;
    q.push(src);
    teams[src-1] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                teams[v-1] = 3 - teams[u-1];
            } else if (teams[v-1] == teams[u-1]) {
        		return false;
			}
        }
    }
    return true;
}

int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	vector<int> dist(n + 1, -1);
	vector<int> teams(n, -1);
	bool result;
	for (int i = 1; i <= n; i++) {
		if (dist[i] == -1) {
			result = bfs(i, n, adj, dist, teams);
			if (!result) {
				cout << "IMPOSSIBLE" << endl;
				return 0;
			}
		}
	}
	
	for (auto el : teams) {
		cout << el << " ";
	}
	
	return 0;
}
