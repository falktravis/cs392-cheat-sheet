#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    int maxSum = 0;
    for (int v : x) maxSum += v;  // max possible sum

    // dp[s] = true if sum s is achievable
    vector<bool> dp(maxSum + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        // Right-to-left to avoid using same coin twice
        for (int s = maxSum; s >= x[i]; s--) {
            if (dp[s - x[i]]) dp[s] = true;
        }
    }

    // Collect all reachable sums (excluding 0)
    vector<int> result;
    for (int s = 1; s <= maxSum; s++) {
        if (dp[s]) result.push_back(s);
    }

    cout << result.size() << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i];
        if (i + 1 < (int)result.size()) cout << " ";
    }
    cout << "\n";

    return 0;
}
