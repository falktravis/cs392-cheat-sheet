#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e15;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    while (cin >> n >> m >> q && (n || m || q)) {

        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) d[i][i] = 0;

        for (int i = 0; i < m; i++) {
            int u, v; ll w; cin >> u >> v >> w;
            d[u][v] = min(d[u][v], w);  // keep cheapest parallel edge
        }

        // Floyd-Warshall
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][k] != INF && d[k][j] != INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

        // Propagate negative cycles:
        // If d[k][k] < 0, node k lies on a negative cycle.
        // Any path that passes through k can be made arbitrarily short -> -INF.
        for (int k = 0; k < n; k++)
            if (d[k][k] < 0)
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (d[i][k] != INF && d[k][j] != INF)
                            d[i][j] = -INF;

        for (int i = 0; i < q; i++) {
            int u, v; cin >> u >> v;
            if      (d[u][v] ==  INF) cout << "Impossible\n";
            else if (d[u][v] == -INF) cout << "-Infinity\n";
            else                      cout << d[u][v] << "\n";
        }
        cout << "\n";
    }
    return 0;
}
