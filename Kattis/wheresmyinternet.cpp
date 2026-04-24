#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // BFS from house 1 (already has internet)
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (!visited[v]) { visited[v] = true; q.push(v); }
    }

    vector<int> unconnected;
    for (int i = 2; i <= n; i++)
        if (!visited[i]) unconnected.push_back(i);

    if (unconnected.empty()) cout << "Connected\n";
    else for (int x : unconnected) cout << x << "\n";

    return 0;
}
