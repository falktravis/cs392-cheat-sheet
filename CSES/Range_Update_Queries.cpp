#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class SegmentTree {
	public:
		vector<long long> tree;
		long long n, size;
		SegmentTree(vector<long long> &ar) {
			size = ar.size();
			n = 1;
    		while (n < size) {
    			n <<= 1;
			}
			tree.resize(2 * n, 0);
			
		    for (ll i = 0; i < size; i++) {
		    	tree[i + n] = ar[i];
			}
			for(long long i=n-1; i > 0; i--) {
				tree[i] = tree[2*i] + tree[2*i+1];	
			}
		}
	
	void update(ll a, ll b, ll u) {
		a += n;
		tree[a] += u;
		while (a > 1) {
			a = a / 2;
			tree[a] = tree[2*a] + tree[2*a+1];
		}
		
		b = b + n + 1;
		if (b < 2 * n) {
			tree[b] -= u;
			while (b > 1) {
				b = b / 2;
				tree[b] = tree[2*b] + tree[2*b+1];
			}
		}
	}
	
	ll query(ll to) {
		ll from = n; // go to the second half of the array
		to += n;
		ll ans = 0; // Initialize ans accordingly
		while (from < to) {
		 	if ((from & 1) == 1) { // 'from' is odd, so it is the right child of its parent,
			 	ans = ans + tree[from]; // then interval includes node 'from’
			 	// ans = max(ans + tree[from]);
			 	// ans = min(ans + tree[from]);
			 	from++; // but doesn't include its parent
			}
			if ((to & 1) == 1) { // 'to' is odd, so it's the right child of its parent,
				to--; // remember that to is exclusive
			 	ans = ans + tree[to];
			 	// ans = max(ans + tree[to]);
			 	// ans = min(ans + tree[to]);
			}
			from >>= 1; // shift right is the same as divide by 2, but a little faster
			to >>= 1;
		}
		return ans;
	}
};



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n, q;
	cin >> n >> q;
	
	vector<long long> myArr(n);
	vector<long long> diffArr(n);
	
	ll temp = 0;
	for (int i = 0; i < n; i++) {
		ll x;
		cin >> x;
		diffArr[i] = x - temp;
		temp = x;
	}
	
	SegmentTree myTree(diffArr);
	
	for (ll Q = 0; Q < q; Q++) {
		ll type;
		cin >> type;
		if (type == 1) {
			ll a, b, u;
			cin >> a >> b >> u;
			myTree.update(a - 1, b - 1, u);
		} else {
			ll k;
			cin >> k;
			ll result = myTree.query(k);
			cout << result << endl;
		}
	}
	
	//cout << "testing: {";
	//for (const auto& element : diffArr) {
	//    cout << element << " ";
	//}
	//cout << "}";
	
	
	return 0;
}
