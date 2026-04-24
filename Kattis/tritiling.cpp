#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // f(0)=1, f(2)=3, f(n) = 4*f(n-2) - f(n-4)
    long long dp[31] = {};
    dp[0] = 1;
    dp[2] = 3;
    for (int i = 4; i <= 30; i += 2)
        dp[i] = 4 * dp[i-2] - dp[i-4];

    int n;
    while (cin >> n && n != -1) {
        if (n % 2 == 1) cout << 0 << "\n";
        else            cout << dp[n] << "\n";
    }
    return 0;
}
