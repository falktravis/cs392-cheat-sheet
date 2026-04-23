using Edge = pair<ll, ll>; // (neighbor, weight)
using PQEntry = pair<ll, ll>; // (distance, node)
const ll INF = 1e18;

void dijkstra(vector<vector<Edge>>& graph, vector<ll>& dist, ll source) {
    dist[source] = 0;
    
    priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        auto [d, node] = pq.top(); 
        pq.pop();
        
        if (d > dist[node]) continue;
        
        for (auto [neighbor, weight] : graph[node]) {
            ll nd = d + weight;
            if (nd < dist[neighbor]) {
                dist[neighbor] = nd;
                pq.push({nd, neighbor});
            }
        }
    }
}
