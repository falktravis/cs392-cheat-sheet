#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<long long> f(MAXN);
    f[1] = 2;
    f[2] = 8;
    for (int i = 3; i < MAXN; i++) {
        f[i] = (6 * f[i-1] % MOD - 7 * f[i-2] % MOD + MOD) % MOD;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << f[n] << "\n";
    }

    return 0;
}
