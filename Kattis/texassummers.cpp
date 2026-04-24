#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    // Index 0 = dorm, 1..n = shady spots, n+1 = class
    vector<pair<ll,ll>> pts(n + 2);
    for (int i = 1; i <= n; i++) cin >> pts[i].first >> pts[i].second;
    cin >> pts[0].first >> pts[0].second;
    cin >> pts[n+1].first >> pts[n+1].second;

    int total = n + 2;

    auto d2 = [&](int i, int j) -> ll {
        ll dx = pts[i].first  - pts[j].first;
        ll dy = pts[i].second - pts[j].second;
        return dx*dx + dy*dy;
    };

    // Dijkstra: minimize sum of squared segment distances
    vector<ll> dist(total, INF);
    vector<int> prev(total, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        ll d = pq.top().first; int u = pq.top().second; pq.pop();
        if (d > dist[u]) continue;
        for (int v = 0; v < total; v++) {
            if (v == u) continue;
            ll nd = dist[u] + d2(u, v);
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push({nd, v});
            }
        }
    }

    // Reconstruct path dorm?...?class
    vector<int> path;
    for (int cur = n+1; cur != 0; cur = prev[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    // Print only intermediate shady spot indices (0-indexed)
    bool any = false;
    for (int x : path) {
        if (x >= 1 && x <= n) { cout << (x-1) << "\n"; any = true; }
    }
    if (!any) cout << "-\n";

    return 0;
}
