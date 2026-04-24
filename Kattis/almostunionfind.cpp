#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> parent, sz;
    vector<ll> sum;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        sum[a] += sum[b];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        int maxNodes = 2*n + m + 1;
        DSU dsu;
        dsu.parent.resize(maxNodes + 1);
        dsu.sz.assign(maxNodes + 1, 0);
        dsu.sum.assign(maxNodes + 1, 0);

        // id[i] = current proxy node for element i
        vector<int> id(n + 1);
        for (int i = 1; i <= n; i++) {
            id[i] = n + i;
            dsu.parent[n+i] = n+i;
            dsu.sz[n+i] = 1;
            dsu.sum[n+i] = i;
        }

        int nextProxy = 2*n + 1;

        while (m--) {
            int op; cin >> op;
            if (op == 1) {
                int p, q; cin >> p >> q;
                dsu.unite(id[p], id[q]);
            } else if (op == 2) {
                int p, q; cin >> p >> q;
                if (dsu.find(id[p]) == dsu.find(id[q])) continue;
                // Detach p from its current component
                int rp = dsu.find(id[p]);
                dsu.sz[rp]--;
                dsu.sum[rp] -= p;
                // Give p a fresh proxy node
                int np = nextProxy++;
                dsu.parent[np] = np;
                dsu.sz[np] = 1;
                dsu.sum[np] = p;
                id[p] = np;
                // Merge into q's component
                dsu.unite(id[p], id[q]);
            } else {
                int p; cin >> p;
                int r = dsu.find(id[p]);
                cout << dsu.sz[r] << " " << dsu.sum[r] << "\n";
            }
        }
    }
    return 0;
}
