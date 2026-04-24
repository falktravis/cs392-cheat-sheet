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


vector<vector<pair<int,int>>> bfs(int i, int j, int n, int m, vector<vector<char>>& grid) {
	vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
	int distance = 0;
    queue<pair<int, int>> q;

	grid[i][j] = '#';
    q.push({i, j});

    while (!q.empty()) {
        pair<int, int> node = q.front(); q.pop();

        if (node.first+1 < n && grid[node.first+1][node.second] != '#') {
        	parent[node.first+1][node.second] = {node.first, node.second};
        	if (grid[node.first+1][node.second] == 'B') {
        		return parent;
			}
        	grid[node.first+1][node.second] = '#';
            q.push({node.first+1, node.second});
        }
        if (node.second+1 < m && grid[node.first][node.second+1] != '#') {
        	parent[node.first][node.second+1] = {node.first, node.second};
        	if (grid[node.first][node.second+1] == 'B') {
        		return parent;
			}
        	grid[node.first][node.second+1] = '#';
            q.push({node.first, node.second+1});
        }
        if (node.first-1 >= 0 && grid[node.first-1][node.second] != '#') {
        	parent[node.first-1][node.second] = {node.first, node.second};
        	if (grid[node.first-1][node.second] == 'B') {
        		return parent;
			}
        	grid[node.first-1][node.second] = '#';
            q.push({node.first-1, node.second});
        }
        if (node.second-1 >= 0 && grid[node.first][node.second-1] != '#') {
        	parent[node.first][node.second-1] = {node.first, node.second};
        	if (grid[node.first][node.second-1] == 'B') {
        		return parent;
			}
        	grid[node.first][node.second-1] = '#';
            q.push({node.first, node.second-1});
        }
    }
    return {};
}


int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	vector<vector<char>> grid(n, vector<char>(m));
	
	pair<int, int> start;
	pair<int, int> end;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char ch;
			cin >> ch;
			if (ch == 'A') {
				start = {i, j};
			} else if (ch == 'B') {
				end = {i, j};
			}
			grid[i][j] = ch;
		}
	}
	
	vector<vector<pair<int,int>>> result;
	result = bfs(start.first, start.second, n, m, grid);
	if (result.empty()) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		string path = "";
	    pair<int,int> cur = end;
	    while (cur != start) {
	        pair<int,int> prev = result[cur.first][cur.second];
	        if (prev.first == cur.first - 1) path += 'D';
	        if (prev.first == cur.first + 1) path += 'U';
	        if (prev.second == cur.second - 1) path += 'R';
	        if (prev.second == cur.second + 1) path += 'L';
	        cur = prev;
	    }
	    reverse(path.begin(), path.end());
	
	    cout << path.size() << "\n";
	    cout << path << "\n";
	}
	return 0;
}
