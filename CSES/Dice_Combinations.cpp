#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n;
	cin >> n;
	
	vector<ll> dp(n+1, 0);
    dp[0] = 1;
	
	for (int i = 1; i <= n; i++) {
		for (int face = 1; face <= 6; face++) {
			if (i - face >= 0)
				dp[i] = (dp[i] + dp[i-face]) % MOD;
		}
	}
	
	cout << dp[n] << endl;

	
	
	return 0;
}
