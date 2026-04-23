using namespace std;
using ll = long long;

using pairll = pair<ll, ll>;   // (dist, node) for Dijkstra

// ============================================================
//  BFS — Unweighted Shortest Path
//  - Single source shortest path on unweighted graphs
//  - Time: O(V + E)
// ============================================================
vector<ll> bfs(ll src, ll n, vector<vector<ll>>& adj) {
    vector<ll> dist(n + 1, -1);
    queue<ll> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        ll u = q.front(); q.pop();

        for (ll v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist; // dist[i] = shortest distance from src to i, -1 if unreachable
}


// ============================================================
//  DFS — Iterative
//  - Component detection, cycle detection, topological sort
//  - Time: O(V + E)
// ============================================================
vector<bool> dfs_iterative(ll src, ll n, vector<vector<ll>>& adj) {
    vector<bool> visited(n + 1, false);
    stack<ll> st;

    st.push(src);

    while (!st.empty()) {
        ll u = st.top(); st.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (ll v : adj[u]) {
            if (!visited[v]) {
                st.push(v);
            }
        }
    }
    return visited;
}

// ============================================================
//  DFS — Recursive
//  - Preferred for tree problems, backtracking, coloring
//  - Increase stack size on Codeforces if needed
//  - Time: O(V + E)
// ============================================================
vector<bool> visited_r; // global to avoid passing by reference

void dfs_recursive(ll u, vector<vector<ll>>& adj) {
    visited_r[u] = true;

    for (ll v : adj[u]) {
        if (!visited_r[v]) {
            dfs_recursive(v, adj);
        }
    }
}

// Usage:
//   visited_r.assign(n + 1, false);
//   dfs_recursive(src, adj);


// ============================================================
//  DIJKSTRA — Weighted Shortest Path (non-negative weights)
//  - Single source shortest path
//  - Time: O((V + E) log V)
// ============================================================
vector<ll> dijkstra(ll src, ll n, vector<vector<pair<ll,ll>>>& adj) {
    const ll INF = 1e18;
    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pairll>, greater<pairll>> pq; // min-heap

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        ll d = pq.top().first;
        ll u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; // stale entry

        for (ll i = 0; i < (ll)adj[u].size(); i++) {
            ll v = adj[u][i].first;
            ll w = adj[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist; // dist[i] = shortest distance from src to i, INF if unreachable
}


// ============================================================
//  MAIN — Example usage
// ============================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // --- Unweighted graph (BFS / DFS) ---
    vector<vector<ll>> adj_uw(n + 1);
    for (ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        adj_uw[u].push_back(v);
        adj_uw[v].push_back(u); // remove for directed
    }

    vector<ll> bfs_dist = bfs(1, n, adj_uw);
    // bfs_dist[node] = shortest hop-distance from node 1

    vector<bool> vis_it = dfs_iterative(1, n, adj_uw);
    // vis_it[node] = true if reachable from node 1

    visited_r.assign(n + 1, false);
    dfs_recursive(1, adj_uw);
    // visited_r[node] = true if reachable from node 1

    // --- Weighted graph (Dijkstra) ---
    vector<vector<pairll>> adj_w(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        adj_w[u].push_back({v, w});
        adj_w[v].push_back({u, w}); // remove for directed
    }

    vector<ll> dijk_dist = dijkstra(1, n, adj_w);
    // dijk_dist[node] = shortest weighted distance from node 1

    return 0;
}
