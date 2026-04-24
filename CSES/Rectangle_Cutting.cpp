#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int dp[501][501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, B;
    cin >> A >> B;

    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            if (i == j) { dp[i][j] = 0; continue; }
            dp[i][j] = INT_MAX;
            // Horizontal cuts (only up to half, since i and a-i is symmetric)
            for (int k = 1; k <= i/2; k++)
                dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i-k][j]);
            // Vertical cuts
            for (int k = 1; k <= j/2; k++)
                dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j-k]);
        }
    }

    cout << dp[A][B] << endl;
    return 0;
}
