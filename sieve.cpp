vector<ll> sieve(n + 1, 0);
for (ll x = 2; x <= n; x++){
	if (sieve[x])
		continue;
	for (ll u = 2 * x; u <= n; u += x){
		sieve[u] = x;
	}
}
