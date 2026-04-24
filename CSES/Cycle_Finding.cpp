#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Edge { int a, b; ll c; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].a >> edges[i].b >> edges[i].c;

    // Initialize all distances to 0 (virtual source connected to all nodes)
    vector<ll> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
    int last = -1;

    // Run n iterations — if nth still relaxes, a negative cycle exists
    for (int iter = 0; iter < n; iter++) {
        last = -1;
        for (int i = 0; i < m; i++) {
            int a = edges[i].a, b = edges[i].b;
            ll  c = edges[i].c;
            if (dist[a] + c < dist[b]) {
                dist[b] = dist[a] + c;
                parent[b] = a;
                last = b;
            }
        }
    }

    if (last == -1) { cout << "NO\n"; return 0; }

    // Walk back n steps to guarantee we land on the cycle itself
    int v = last;
    for (int i = 0; i < n; i++)
        v = parent[v];

    // Collect cycle until we revisit v
    vector<bool> visited(n + 1, false);
    vector<int> cycle;
    int cur = v;
    while (!visited[cur]) {
        visited[cur] = true;
        cycle.push_back(cur);
        cur = parent[cur];
    }
    cycle.push_back(cur);  // closing node = v again
    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int i = 0; i < (int)cycle.size(); i++)
        cout << cycle[i] << " ";
    cout << "\n";
    return 0;
}
