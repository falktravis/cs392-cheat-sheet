<<<<<<< Updated upstream
// Adjacency Matrix
=======



>>>>>>> Stashed changes
queue<ll> q;
vector<bool> visited(n, false);
q.push(0);
visited(0) = true;
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


// Adjacency List
queue<ll> q;
vector<bool> visited(n, false);
q.push(0);
visited(0) = true;
while (!q.empty()){
	ll front = q.front();
	q.pop();
	
	for (ll neighbor : adjList[front]){
		if (!visited[neighbor]){
			q.push(neighbor);
			visited[neighbor] = true;
		}
	}

}
