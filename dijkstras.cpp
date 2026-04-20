using Edge = pair<ll, ll>; // (neighbor, weight)
using PQEntry = pair<ll, ll>; // (node, distance)

void dijkstra(vector<vector<Edge>>& graph, vector<ll>& dist, ll source) {
	dist[source] = 0;
	
	priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> pq;
	pq.push({source, 0});
	
	while (!pq.empty()) {
		auto [node, _] = pq.top();
		pq.pop();
		
		for (auto [neighbor, weight] : graph[node]) {
			int new_dist = dist[node] + weight;
			
			if (new_dist < dist[neighbor]) {
				dist[neighbor] = new_dist;
				pq.push({neighbor, new_dist});
			}
		}
	}
}
