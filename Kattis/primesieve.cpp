#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) count++;
    }

    cout << count << "\n";

    while (q--) {
        int x;
        cin >> x;
        cout << (is_prime[x] ? 1 : 0) << "\n";
    }

    return 0;
}
