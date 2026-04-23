struct DSU {
	vector<ll> parent;
	vector<ll> size;
	
	DSU(ll n) {
		parent.resize(n);
		size.resize(n, 1);
		iota(parent.begin(), parent.end(), 0);
	}
	
	ll find(ll i) {
		if (parent[i] == i) {
			return i;
		}
		
		return parent[i] = find(parent[i]);
	}
	
	bool unite(ll i, ll j) {
		ll root_i = find(i);
		ll root_j = find(j);
		
		if (root_i == root_j) {
			return false;
		}
		
		if (size[root_i] < size[root_j]) {
			swap(root_i, root_j);
		}
		
		parent[root_j] = root_i;
		size[root_i] += size[root_j];
		return true;
	}
};
