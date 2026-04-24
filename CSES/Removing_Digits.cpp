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

int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n;
	cin >> n;
	
	vector<ll> dp(n + 1, 1e9);
	dp[0] = 0;
		
	for (ll i = 1; i <= n; i++) {
		string s = to_string(i);
        for (char c : s) {
            int digit = c - '0';
            if (digit != 0) {
            	dp[i] = min(dp[i], dp[i - digit] + 1);
			}  
        }
		
	}
	cout << dp[n] << endl;
	
	return 0;
}
