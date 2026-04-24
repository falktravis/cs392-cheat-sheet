#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll NEG_INF = -1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1), radj(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
        indegree[b]++;
    }

    // Topological sort + DP
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0) q.push(i);

    vector<ll> dist(n + 1, NEG_INF);
    dist[1] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[u] != NEG_INF)
                dist[v] = max(dist[v], dist[u] + 1);
            if (--indegree[v] == 0)
                q.push(v);
        }
    }

    if (dist[n] == NEG_INF) { cout << "IMPOSSIBLE\n"; return 0; }

    // Reconstruct: walk back from n using dist values
    vector<int> path;
    int cur = n;
    while (cur != 1) {
        path.push_back(cur);
        for (int prev : radj[cur])
            if (dist[prev] == dist[cur] - 1) { cur = prev; break; }
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << " \n"[i == (int)path.size()-1];

    return 0;
}
