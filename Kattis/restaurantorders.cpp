#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; i++) cin >> price[i];

    int q;
    cin >> q;
    vector<int> orders(q);
    int maxOrder = 0;
    for (int i = 0; i < q; i++) { cin >> orders[i]; maxOrder = max(maxOrder, orders[i]); }

    // Unbounded knapsack counting distinct multisets (outer=items, inner=forward)
    // Cap at 2 — we only care whether count is 0, 1, or 2+
    vector<int> ways(maxOrder + 1, 0);
    ways[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int s = price[i]; s <= maxOrder; s++)
            ways[s] = min(2, ways[s] + ways[s - price[i]]);

    for (int i = 0; i < q; i++) {
        int target = orders[i];
        if (ways[target] == 0) {
            cout << "Impossible\n";
        } else if (ways[target] >= 2) {
            cout << "Ambiguous\n";
        } else {
            // Reconstruct: greedily pick smallest-indexed item that keeps ways==1
            vector<int> items;
            int s = target;
            while (s > 0) {
                for (int j = 1; j <= n; j++) {
                    if (price[j] <= s && ways[s - price[j]] == 1) {
                        items.push_back(j);
                        s -= price[j];
                        break;
                    }
                }
            }
            for (int j = 0; j < (int)items.size(); j++)
                cout << items[j] << " \n"[j + 1 == (int)items.size()];
        }
    }
    return 0;
}
