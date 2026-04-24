#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> d[i][j];

    // Reconstruct tree = MST of complete graph with edge weights d[i][j]
    // Prim's algorithm O(n^2)
    vector<bool> inMST(n, false);
    vector<int> minDist(n, INT_MAX);
    vector<int> parent(n, -1);
    minDist[0] = 0;

    for (int iter = 0; iter < n; iter++) {
        // Pick cheapest unvisited node
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!inMST[i] && (u == -1 || minDist[i] < minDist[u]))
                u = i;

        inMST[u] = true;
        if (parent[u] != -1)
            cout << (parent[u]+1) << " " << (u+1) << "\n";

        // Relax edges from u
        for (int v = 0; v < n; v++)
            if (!inMST[v] && d[u][v] < minDist[v]) {
                minDist[v] = d[u][v];
                parent[v] = u;
            }
    }

    return 0;
}
