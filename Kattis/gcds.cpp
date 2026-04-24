#include <iostream>
#include <vector>
#include <set>
using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<int> all_gcds;
    vector<int> prev;  // distinct GCDs of subarrays ending at i-1

    for (int i = 0; i < n; i++) {
        vector<int> curr;
        curr.push_back(a[i]);  // subarray [i..i]
        for (int g : prev) {
            int ng = gcd(g, a[i]);
            if (curr.back() != ng) curr.push_back(ng);
        }
        for (int g : curr) all_gcds.insert(g);
        prev = curr;
    }

    cout << all_gcds.size() << "\n";
    return 0;
}
