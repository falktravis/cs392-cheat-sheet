#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, sz, items;

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    parent.resize(k+1); sz.assign(k+1, 1); items.assign(k+1, 0);
    for (int i = 1; i <= k; i++) parent[i] = i;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        int ra = find(a), rb = find(b);

        if (ra == rb) {
            // Same component: fits if there's still a free drawer
            if (items[ra] < sz[ra]) { items[ra]++; cout << "LADICA\n"; }
            else                      cout << "SMECE\n";
        } else {
            // Merge components, then check if item fits
            if (sz[ra] < sz[rb]) swap(ra, rb);
            parent[rb] = ra;
            sz[ra]    += sz[rb];
            items[ra] += items[rb];  // combine stored items (NOT +1 yet)
            if (items[ra] < sz[ra]) { items[ra]++; cout << "LADICA\n"; }
            else                      cout << "SMECE\n";
        }
    }
    return 0;
}
