#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;
    dist[0][0] = 0;
    q.push(make_pair(0, 0));

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();

        int d = grid[r][c] - '0';
        if (d == 0) continue;  // digit 0: no valid moves

        for (int dir = 0; dir < 4; dir++) {
            int nr = r + dr[dir] * d;
            int nc = c + dc[dir] * d;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push(make_pair(nr, nc));
        }
    }

    cout << dist[n-1][m-1] << "\n";
    return 0;
}
