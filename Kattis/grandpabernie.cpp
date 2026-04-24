#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string, vector<int>> trips;

    for (int i = 0; i < n; i++) {
        string country; int year;
        cin >> country >> year;
        trips[country].push_back(year);
    }

    // Sort each country's trips chronologically
    for (auto& p : trips)
        sort(p.second.begin(), p.second.end());

    int q; cin >> q;
    while (q--) {
        string country; int k;
        cin >> country >> k;
        cout << trips[country][k-1] << "\n";
    }
    return 0;
}
