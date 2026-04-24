#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = 1e18;

vector<ll> dijkstra(int src, int n, vector<vector<pair<int,ll>>>& adj) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        ll d = pq.top().first; int u = pq.top().second; pq.pop();
        if (d > dist[u]) continue;
        for (auto& e : adj[u]) {
            int v = e.first; ll w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    struct Edge { int u, v; ll w; };
    vector<Edge> edges(m);
    vector<vector<pair<int,ll>>> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> ds = dijkstra(0, n, adj);      // distances from entrance
    vector<ll> dt = dijkstra(n-1, n, adj);    // distances from peak
    ll shortest = ds[n-1];

    // Edge (u,v,w) is on some shortest path if either orientation fits
    ll total = 0;
    for (auto& e : edges) {
        if (e.u == e.v) continue;  // skip self-loops
        if ((ds[e.u] + e.w + dt[e.v] == shortest) ||
            (ds[e.v] + e.w + dt[e.u] == shortest))
            total += e.w;
    }

    cout << total * 2 << "\n";
    return 0;
}
