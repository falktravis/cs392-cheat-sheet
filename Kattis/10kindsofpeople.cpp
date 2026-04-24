#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<int>> comp;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

void bfs(int sr, int sc, int id) {
    queue<pair<int,int>> q;
    q.push(make_pair(sr, sc));
    comp[sr][sc] = id;
    char ch = grid[sr][sc];
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (comp[nr][nc] != -1) continue;
            if (grid[nr][nc] != ch) continue;
            comp[nr][nc] = id;
            q.push(make_pair(nr, nc));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    grid.resize(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    // Label every cell with its component id
    comp.assign(n, vector<int>(m, -1));
    int num_comp = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (comp[i][j] == -1)
                bfs(i, j, num_comp++);

    int q; cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;   // 1-indexed input ? 0-indexed

        if (comp[r1][c1] == comp[r2][c2])
            cout << (grid[r1][c1] == '0' ? "binary" : "decimal") << "\n";
        else
            cout << "neither\n";
    }
    return 0;
}
