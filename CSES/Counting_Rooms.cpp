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


void bfs(int i, int j, int n, int m, vector<vector<char>>& grid) {
    queue<pair<int, int>> q;

	grid[i][j] = '#';
    q.push({i, j});

    while (!q.empty()) {
        pair<int, int> node = q.front(); q.pop();

        if (node.first+1 < n && grid[node.first+1][node.second] == '.') {
        	grid[node.first+1][node.second] = '#';
            q.push({node.first+1, node.second});
        }
        if (node.second+1 < m && grid[node.first][node.second+1] == '.') {
        	grid[node.first][node.second+1] = '#';
            q.push({node.first, node.second+1});
        }
        if (node.first-1 >= 0 && grid[node.first-1][node.second] == '.') {
        	grid[node.first-1][node.second] = '#';
            q.push({node.first-1, node.second});
        }
        if (node.second-1 >= 0 && grid[node.first][node.second-1] == '.') {
        	grid[node.first][node.second-1] = '#';
            q.push({node.first, node.second-1});
        }
    }
}


int main() {
	//Fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	vector<vector<char>> grid(n, vector<char>(m));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char ch;
			cin >> ch;
			grid[i][j] = ch;
		}
	}
	
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '.') {
				bfs(i, j, n, m, grid);
				count++;
			}
		}
	}
	cout << count;
	return 0;
}
