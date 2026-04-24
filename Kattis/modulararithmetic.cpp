#include <iostream>
using namespace std;
typedef long long ll;

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1;          // no inverse if gcd(a,m) != 1
    return (x % m + m) % m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll p, n;
    while (cin >> p >> n && (p || n)) {
        while (n--) {
            ll a, b; char op;
            cin >> a >> op >> b;
            a = ((a % p) + p) % p;
            b = ((b % p) + p) % p;

            if      (op == '+') cout << (a + b) % p       << "\n";
            else if (op == '-') cout << (a - b + p) % p   << "\n";
            else if (op == '*') cout << a * b % p          << "\n";
            else {  // division
                if (b == 0) { cout << "-1\n"; continue; }
                ll inv = modinv(b, p);
                if (inv == -1) cout << "-1\n";
                else           cout << a * inv % p << "\n";
            }
        }
    }
    return 0;
}
