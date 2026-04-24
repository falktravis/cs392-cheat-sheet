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

vector<int> bfs(int src, int n, vector<vector<int>>& adj, vector<int>& parent) {
    vector<int> dist(n + 1, -1);
    queue<int> q;

	parent[src] = -1;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
            	parent[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist; // dist[i] = shortest distance from src to i, -1 if unreachable
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
	vector<int> parent(n + 1);
	vector<int> dist = bfs(1, n, adj, parent);
	
	if (dist[n] == -1) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		int curr = n;
		vector<int> path;
		while (curr != -1) {
			path.push_back(curr);
			curr = parent[curr];
		}
		reverse(path.begin(), path.end());
		cout << path.size() << endl;
		for (auto el : path) {
			cout << el << " ";
		}
	}
	
	return 0;
}
