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

void dfs_iterative(int src, int n, vector<vector<int>>& adj, vector<bool>& visited) {
    stack<int> st;

    st.push(src);

    while (!st.empty()) {
        int u = st.top(); st.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                st.push(v);
            }
        }
    }
    return;
}

int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	vector<bool> visited(n + 1, false);
	vector<int> representatives;
	int count = 0;
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			representatives.push_back(i); 
			dfs_iterative(i, n, adj, visited);
			count++;
		}
	}
	cout << count - 1 << endl;
	
	for (int i = 0; i < representatives.size() - 1; i++) {
		cout << representatives[i] << " " << representatives[i+1] << endl;
	}
	
	return 0;
}
