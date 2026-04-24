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
	
	ll n_coins, sum;
	cin >> n_coins >> sum;

	vector<ll> coins;
	for (ll i = 0; i<n_coins; i++){
		ll temp;
		cin >> temp;
		coins.push_back(temp);
	}
	
	vector<ll> dp(sum + 1, 0);
	dp[0] = 1;
		
	for (ll dpx = 1; dpx <= sum; dpx++) {
		for (ll idx = 0; idx < coins.size(); idx++) {
			if (dpx - coins[idx] >= 0) {
				dp[dpx] = (dp[dpx] + dp[dpx - coins[idx]]) % MOD;
			}
		}
	}
	cout << dp[sum] << endl;
	
	
	return 0;
}
