#include <iostream>
#include <vector>
using namespace std;

int parent[100001], sz[100001];
int num_components, max_size;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // path compression
    return parent[x];
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;  // already same component

    // Union by size: attach smaller tree under larger
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];

    num_components--;
    max_size = max(max_size, sz[a]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Initially every city is its own component
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    num_components = n;
    max_size = 1;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
        cout << num_components << " " << max_size << "\n";
    }

    return 0;
}
