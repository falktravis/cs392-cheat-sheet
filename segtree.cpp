class SegmentTree {
	public:
	vector<ll> tree;
	ll n;
	
	SegmentTree(vector<ll> &ar){
		n = ar.size();
		tree.resize(n);
		tree.insert(tree.end(), ar.begin(), ar.end());
		for(ll i=n-1; i >0; i--)
			tree[i] = tree[2*i] ^ tree[2*i+1];
	}
	
	void update(int i, int value) {
		i += n;
		tree[i] = value;
		while (i > 1) {
			i = i / 2;
			tree[i] = tree[2 * i] ^ tree[2 * i + 1];
		}
	}
	
	ll query(ll from, ll to) {
		from += n; // go to the second half of the array
		to += n;
		
		ll ans = 0; // Initialize ans accordingly
		
		while (from < to) {
			if ((from & 1) == 1) { // 'from' is odd, so it is the right child of its parent,
				ans = ans ^ tree[from]; // then interval includes node 'from’
				from++; // but doesn't include its parent
			}
			
			if ((to & 1) == 1) { // 'to' is odd, so it's the right child of its parent,
				to--; // remember that to is exclusive
				ans = ans ^ tree[to];
			}
			
			from >>= 1; // shift right is the same as divide by 2, but a little faster
			to >>= 1;
		}
		return ans;
	}
};
