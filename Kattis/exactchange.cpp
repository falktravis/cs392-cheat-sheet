#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        int price, n;
        cin >> price >> n;

        vector<int> coins(n);
        int total = 0;
        for (int i = 0; i < n; i++) { cin >> coins[i]; total += coins[i]; }

        // dp[s] = min coins to reach sum s exactly (INT_MAX = unreachable)
        vector<int> dp(total + 1, INT_MAX);
        dp[0] = 0;

        // 0/1 knapsack — right-to-left to use each coin at most once
        for (int i = 0; i < n; i++)
            for (int s = total; s >= coins[i]; s--)
                if (dp[s - coins[i]] != INT_MAX)
                    dp[s] = min(dp[s], dp[s - coins[i]] + 1);

        // Find smallest reachable sum >= price, with fewest coins
        for (int s = price; s <= total; s++) {
            if (dp[s] != INT_MAX) {
                cout << s << " " << dp[s] << "\n";
                break;
            }
        }
    }
    return 0;
}
