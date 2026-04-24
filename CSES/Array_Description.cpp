#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    vector<long long> dp(m + 1, 0);

    // Initialize first position
    if (x[0] == 0) {
        for (int v = 1; v <= m; v++) dp[v] = 1;
    } else {
        dp[x[0]] = 1;
    }

    // Transition
    for (int i = 1; i < n; i++) {
        vector<long long> ndp(m + 1, 0);

        for (int v = 1; v <= m; v++) {
            // Skip values not allowed at this position
            if (x[i] != 0 && x[i] != v) continue;

            // Sum contributions from v-1, v, v+1
            for (int prev = v - 1; prev <= v + 1; prev++) {
                if (prev < 1 || prev > m) continue;
                ndp[v] = (ndp[v] + dp[prev]) % MOD;
            }
        }

        dp = ndp;
    }

    // Sum all valid endings
    long long ans = 0;
    for (int v = 1; v <= m; v++) {
        ans = (ans + dp[v]) % MOD;
    }

    cout << ans << endl;
    return 0;
}
