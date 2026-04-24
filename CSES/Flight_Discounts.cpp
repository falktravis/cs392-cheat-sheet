#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

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

    // State: (node, coupon_used)
    // dist[u][0] = shortest to u with coupon still available
    // dist[u][1] = shortest to u with coupon already spent
    vector<vector<ll>> dist(n + 1, vector<ll>(2, INF));
    // pq: (distance, (node, used))
    priority_queue<pair<ll,pair<int,int>>,
                   vector<pair<ll,pair<int,int>>>,
                   greater<pair<ll,pair<int,int>>>> pq;

    dist[1][0] = 0;
    pq.push({0, {1, 0}});

    while (!pq.empty()) {
        ll d    = pq.top().first;
        int u   = pq.top().second.first;
        int used = pq.top().second.second;
        pq.pop();

        if (d > dist[u][used]) continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            ll  w = adj[u][i].second;

            // Option 1: don't use coupon on this edge
            if (dist[u][used] + w < dist[v][used]) {
                dist[v][used] = dist[u][used] + w;
                pq.push({dist[v][used], {v, used}});
            }

            // Option 2: use coupon on this edge (only if not yet used)
            if (used == 0 && dist[u][0] + w/2 < dist[v][1]) {
                dist[v][1] = dist[u][0] + w/2;
                pq.push({dist[v][1], {v, 1}});
            }
        }
    }

    cout << dist[n][1] << "\n";
    return 0;
}
