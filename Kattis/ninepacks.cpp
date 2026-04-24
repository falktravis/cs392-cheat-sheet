#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nh;
    cin >> nh;
    vector<int> hdogs(nh);
    for (int i = 0; i < nh; i++) cin >> hdogs[i];

    int nb;
    cin >> nb;
    vector<int> buns(nb);
    for (int i = 0; i < nb; i++) cin >> buns[i];

    // hdp[s] = min hotdog packs to get exactly s hotdogs
    // bdp[s] = min bun packs to get exactly s buns
    // Answer = min over s > 0 where both are reachable: hdp[s] + bdp[s]

    int maxH = 0, maxB = 0;
    for (int x : hdogs) maxH += x;
    for (int x : buns)  maxB += x;

    const int INF = INT_MAX / 2;
    vector<int> hdp(maxH + 1, INF);
    vector<int> bdp(maxB + 1, INF);
    hdp[0] = 0;
    bdp[0] = 0;

    // 0/1 knapsack — each pack used at most once
    for (int i = 0; i < nh; i++)
        for (int s = maxH; s >= hdogs[i]; s--)
            if (hdp[s - hdogs[i]] != INF)
                hdp[s] = min(hdp[s], hdp[s - hdogs[i]] + 1);

    for (int i = 0; i < nb; i++)
        for (int s = maxB; s >= buns[i]; s--)
            if (bdp[s - buns[i]] != INF)
                bdp[s] = min(bdp[s], bdp[s - buns[i]] + 1);

    int ans = INF;
    int limit = min(maxH, maxB);
    for (int s = 1; s <= limit; s++)
        if (hdp[s] != INF && bdp[s] != INF)
            ans = min(ans, hdp[s] + bdp[s]);

    if (ans == INF) cout << "impossible\n";
    else            cout << ans << "\n";
    return 0;
}
