#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int round10(int x) {
    return ((x + 5) / 10) * 10;  // round to nearest 10, half rounds up
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        pre[i] = pre[i-1] + x;
    }

    // k dividers = up to k+1 contiguous groups
    // dp[i] = min cost covering items 1..i using exactly g groups so far
    // Iterate g from 1 to min(k+1, n), track best answer at dp[n]

    int maxGroups = min(k + 1, n);
    const int INF = INT_MAX / 2;

    vector<int> prev_dp(n + 1, INF);
    prev_dp[0] = 0;

    int ans = INF;
    for (int g = 1; g <= maxGroups; g++) {
        vector<int> cur_dp(n + 1, INF);
        for (int i = 1; i <= n; i++) {
            for (int m = g - 1; m < i; m++) {
                if (prev_dp[m] == INF) continue;
                int cost = round10(pre[i] - pre[m]);
                cur_dp[i] = min(cur_dp[i], prev_dp[m] + cost);
            }
        }
        ans = min(ans, cur_dp[n]);
        prev_dp = cur_dp;
    }

    cout << ans << "\n";
    return 0;
}
