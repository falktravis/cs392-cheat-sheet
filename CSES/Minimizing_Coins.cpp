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

const int INF = 1e9;

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
	
	vector<ll> dp(sum + 1, INF);
	dp[0] = 0;
	
	for (ll dpx = 1; dpx <= sum; dpx++) {
		for (ll idx = 0; idx < coins.size(); idx++) {
			if (dpx - coins[idx] >= 0) {
				dp[dpx] = min(dp[dpx], dp[dpx - coins[idx]] + 1);
			}
		}
	}
	if (dp[sum] >= INF) {
		cout << -1 << endl;
	} else {
		cout << dp[sum] << endl;
	}
	
	
	return 0;
}
