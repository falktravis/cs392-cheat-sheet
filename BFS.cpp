queue<ll> q;
vector<bool> visited(n, false);
q.push(0);
while (!q.empty()){
	ll front = q.front();
	q.pop();
	
	for(ll i = 0; i<n; i++){
		if (adjMatrix[front][i] == 1){						
			if (!visited[i]){
				q.push(i);
				visited[i] = true;
			}
		}
	}
}
