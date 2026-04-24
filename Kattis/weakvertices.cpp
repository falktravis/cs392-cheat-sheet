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
	
	int n;
	cin >> n;
	while (n != -1) {
		vector<vector<int>> adj(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int val;
				cin >> val;
				adj[i][j] = val;
			}
		}
		
		vector<int> weak;
		for (int i = 0; i < n; i++) {
			bool inTriangle = false;
			for (int j = 0; j < n && !inTriangle; j++) {
				for (int k = j + 1; k < n  && !inTriangle; k++) {
					if (adj[i][j] && adj[i][k] && adj[k][j]) {
						inTriangle = true;
					}
				}
			}
			
			if (!inTriangle) {
				weak.push_back(i);
			}
		}
		
		for (auto el : weak) {
			cout << el << " ";
		}
		cout << endl;
		cin >> n;
	}
	
	return 0;
}
