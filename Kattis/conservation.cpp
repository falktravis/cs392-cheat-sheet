#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;

        vector<int> lab(n + 1);
        for (int i = 1; i <= n; i++) cin >> lab[i];

        vector<vector<int>> adj(n + 1);
        vector<int> indegree(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            indegree[b]++;
        }

        // Try starting in each lab, return min switches
        auto simulate = [&](int start_lab) {
            vector<int> ind = indegree;
            queue<int> qq[2];
            for (int i = 1; i <= n; i++)
                if (ind[i] == 0)
                    qq[lab[i] - 1].push(i);

            int cur = start_lab, switches = 0;

            while (qq[0].size() + qq[1].size() > 0) {
                // Forced switch if current lab has nothing ready
                if (qq[cur].empty()) { cur ^= 1; switches++; }

                // Drain everything ready in current lab
                while (!qq[cur].empty()) {
                    int u = qq[cur].front(); qq[cur].pop();
                    for (int v : adj[u])
                        if (--ind[v] == 0)
                            qq[lab[v] - 1].push(v);
                }

                // Voluntary switch if other lab now has work
                if (!qq[cur ^ 1].empty()) { cur ^= 1; switches++; }
            }
            return switches;
        };

        cout << min(simulate(0), simulate(1)) << "\n";
    }
    return 0;
}
