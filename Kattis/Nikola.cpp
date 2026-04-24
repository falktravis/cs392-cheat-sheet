#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++) cin >> cost[i];

    // State: (pos, last_jump_size k)
    // Forward:  jump k+1 squares ahead, k becomes k+1
    // Backward: jump k squares back,    k stays k
    // maxK = n (not sqrt(n) — see below)

    int maxK = n;
    const int INF = INT_MAX / 2;
    vector<vector<int>> dist(n + 1, vector<int>(maxK + 1, INF));

    priority_queue<tuple<int,int,int>,
                   vector<tuple<int,int,int>>,
                   greater<tuple<int,int,int>>> pq;

    dist[1][0] = 0;
    pq.push(make_tuple(0, 1, 0));

    while (!pq.empty()) {
        int d   = get<0>(pq.top());
        int pos = get<1>(pq.top());
        int k   = get<2>(pq.top());
        pq.pop();

        if (d > dist[pos][k]) continue;

        // Forward: jump size k+1
        int nk = k + 1;
        int fwd = pos + nk;
        if (fwd <= n && nk <= maxK) {
            int nd = d + cost[fwd];
            if (nd < dist[fwd][nk]) {
                dist[fwd][nk] = nd;
                pq.push(make_tuple(nd, fwd, nk));
            }
        }

        // Backward: jump size k (unchanged)
        if (k > 0) {
            int bwd = pos - k;
            if (bwd >= 1) {
                int nd = d + cost[bwd];
                if (nd < dist[bwd][k]) {
                    dist[bwd][k] = nd;
                    pq.push(make_tuple(nd, bwd, k));
                }
            }
        }
    }

    int ans = INF;
    for (int k = 1; k <= maxK; k++)
        ans = min(ans, dist[n][k]);

    cout << ans << "\n";
    return 0;
}
