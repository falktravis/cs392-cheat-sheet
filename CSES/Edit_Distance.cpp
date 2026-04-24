#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    // dp[i][j] = edit distance between a[0..i-1] and b[0..j-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base cases: transforming to/from empty string
    for (int i = 0; i <= n; i++) dp[i][0] = i;  // delete all chars from a
    for (int j = 0; j <= m; j++) dp[0][j] = j;  // insert all chars of b

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1];          // chars match, no op needed
            } else {
                dp[i][j] = 1 + min(
                    dp[i-1][j],    // delete from a
                    min(dp[i][j-1],    // insert into a
                    dp[i-1][j-1])   // replace
                );
            }
        }
    }

    cout << dp[n][m] << endl;
    return 0;
}
