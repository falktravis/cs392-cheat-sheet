#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, sz;

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
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    parent.resize(n); sz.assign(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;

    while (m--) {
        char op; int a, b; cin >> op >> a >> b;
        if (op == '=') unite(a, b);
        else cout << (find(a) == find(b) ? "yes" : "no") << "\n";
    }
    return 0;
}
