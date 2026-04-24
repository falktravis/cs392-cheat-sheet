#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Edge {
    ll cost;
    int a, b;
    bool operator<(const Edge& o) const { return cost < o.cost; }
};

int parent[100001], sz[100001];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].a >> edges[i].b >> edges[i].cost;

    sort(edges.begin(), edges.end());

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    ll total = 0;
    int edges_used = 0;

    for (int i = 0; i < m; i++) {
        if (unite(edges[i].a, edges[i].b)) {
            total += edges[i].cost;
            if (++edges_used == n - 1) break;
        }
    }

    if (edges_used < n - 1)
        cout << "IMPOSSIBLE\n";
    else
        cout << total << "\n";

    return 0;
}
