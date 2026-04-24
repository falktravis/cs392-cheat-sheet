#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class SegmentTree {
	public:
		vector<long long> tree;
		long long n;
		SegmentTree(vector<long long> &ar) {
			n = ar.size();
			tree.resize(n);
			tree.insert(tree.end(), ar.begin(), ar.end());
			for(long long i=n-1; i > 0; i--) {
				tree[i] = tree[2*i] + tree[2*i+1];	
			}
		}
	
	void update(long long i, long long value) {
		i += n;
		tree[i] = value;
		while (i > 1) {
			i = i / 2;
			tree[i] = tree[2*i] + tree[2*i+1];
		}
	}
	
	long long query(long long from, long long to) {
		from += n; // go to the second half of the array
		to += n;
		long long ans = 0; // Initialize ans accordingly
		while (from < to) {
		 	if ((from & 1) == 1) { // 'from' is odd, so it is the right child of its parent,
			 	ans = ans + tree[from]; // then interval includes node 'from’
			 	from++; // but doesn't include its parent
			}
			if ((to & 1) == 1) { // 'to' is odd, so it's the right child of its parent,
				to--; // remember that to is exclusive
			 	ans = ans + tree[to];
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
	
	for (long long i = 0; i < n; i++) {
		long long val;
		cin >> val;
		myArr[i] = val;
	}
	
	SegmentTree mySegmentTree(myArr);
	
	for (int Q = 0; Q < q; Q++) {
		long long a, b, c;
		cin >> c >> a >> b;
		
		if (c == 1) {
			mySegmentTree.update(a-1, b);
		} else {
			long long answer = mySegmentTree.query(a-1, b);
			cout << answer << endl;
		}
	}
	return 0;
}
