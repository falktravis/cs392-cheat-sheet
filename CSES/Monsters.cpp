#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<int>> mdist, pdist;
vector<vector<pair<int,int>>> prev_cell;

int dr[] = {1, -1, 0, 0};
int dc[] = {0,  0,-1, 1};
char dname[] = {'D','U','L','R'};

bool inBounds(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    grid.resize(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    // Phase 1: multi-source BFS from all monsters simultaneously
    mdist.assign(n, vector<int>(m, INT_MAX));
    queue<pair<int,int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'M') {
                mdist[i][j] = 0;
                q.push({i, j});
            }
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (inBounds(nr, nc) && grid[nr][nc] != '#' && mdist[nr][nc] == INT_MAX) {
                mdist[nr][nc] = mdist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    // Phase 2: BFS from player, only through cells where player arrives strictly first
    pdist.assign(n, vector<int>(m, INT_MAX));
    prev_cell.assign(n, vector<pair<int,int>>(m, {-1,-1}));
    int sr = -1, sc = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'A') { sr = i; sc = j; }

    pdist[sr][sc] = 0;
    q.push({sr, sc});
    int er = -1, ec = -1;

    if (sr == 0 || sr == n-1 || sc == 0 || sc == m-1)
        er = sr, ec = sc;

    while (!q.empty() && er == -1) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (!inBounds(nr, nc) || grid[nr][nc] == '#' || pdist[nr][nc] != INT_MAX)
                continue;
            int np = pdist[r][c] + 1;
            if (np >= mdist[nr][nc]) continue;  // monster gets there same time or sooner
            pdist[nr][nc] = np;
            prev_cell[nr][nc] = {r, c};
            q.push({nr, nc});
            if (nr == 0 || nr == n-1 || nc == 0 || nc == m-1) {
                er = nr; ec = nc; break;
            }
        }
    }

    if (er == -1) { cout << "NO\n"; return 0; }

    // Reconstruct path from exit back to start
    string path = "";
    int r = er, c = ec;
    while (r != sr || c != sc) {
        auto [pr, pc] = prev_cell[r][c];
        for (int d = 0; d < 4; d++)
            if (pr + dr[d] == r && pc + dc[d] == c) { path += dname[d]; break; }
        r = pr; c = pc;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n" << path.size() << "\n" << path << "\n";
    return 0;
}
