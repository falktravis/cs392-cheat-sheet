#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> adj[100001];
int parent[100001];
bool visited[100001];
int cycle_start, cycle_end;

bool dfs(int u, int par) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (v == par) continue;        // skip the edge we came from
        if (visited[v]) {
            // Found back edge u->v: cycle goes v...u->v
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        parent[v] = u;
        if (dfs(v, u)) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            parent[i] = -1;
            if (dfs(i, -1)) {
                // Walk back from cycle_end to cycle_start via parent pointers
                vector<int> cycle;
                cycle.push_back(cycle_start);
                for (int v = cycle_end; v != cycle_start; v = parent[v])
                    cycle.push_back(v);
                cycle.push_back(cycle_start);  // close the loop

                cout << cycle.size() << "\n";
                for (int v : cycle) cout << v << " ";
                cout << "\n";
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
