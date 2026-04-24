#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll>  dist(n + 1, INF);
    vector<ll>  ways(n + 1, 0);
    vector<int> minedge(n + 1, 0);
    vector<int> maxedge(n + 1, 0);

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0;
    ways[1] = 1;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d  = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            ll  w = adj[u][i].second;
            ll  nd = dist[u] + w;

            if (nd < dist[v]) {
                // Strictly better: replace all previous path info
                dist[v]    = nd;
                ways[v]    = ways[u];
                minedge[v] = minedge[u] + 1;
                maxedge[v] = maxedge[u] + 1;
                pq.push({nd, v});
            } else if (nd == dist[v]) {
                // Equally good: accumulate counts, update min/max edges
                ways[v]    = (ways[v] + ways[u]) % MOD;
                minedge[v] = min(minedge[v], minedge[u] + 1);
                maxedge[v] = max(maxedge[v], maxedge[u] + 1);
            }
        }
    }

    cout << dist[n] << " " << ways[n] << " "
         << minedge[n] << " " << maxedge[n] << "\n";
    return 0;
}
