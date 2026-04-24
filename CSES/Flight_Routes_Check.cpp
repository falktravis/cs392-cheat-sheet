#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, m;
vector<int> adj[100001], radj[100001];
bool visited[100001];
int comp[100001];
vector<int> order;

void dfs1(int start) {
    stack<pair<int,int> > st;
    st.push(make_pair(start, 0));
    visited[start] = true;
    while (!st.empty()) {
        int u    = st.top().first;
        int& idx = st.top().second;
        if (idx < (int)adj[u].size()) {
            int v = adj[u][idx++];
            if (!visited[v]) {
                visited[v] = true;
                st.push(make_pair(v, 0));
            }
        } else {
            order.push_back(u);
            st.pop();
        }
    }
}

void dfs2(int start, int c) {
    stack<int> st;
    st.push(start);
    comp[start] = c;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int i = 0; i < (int)radj[u].size(); i++) {
            int v = radj[u][i];
            if (!comp[v]) { comp[v] = c; st.push(v); }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    // Pass 1: DFS on original graph, record finish order
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs1(i);

    // Pass 2: DFS on reversed graph in reverse finish order
    int num_scc = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--)
        if (!comp[order[i]]) dfs2(order[i], ++num_scc);

    if (num_scc == 1) { cout << "YES\n"; return 0; }

    // num_scc = source SCC, 1 = sink SCC in condensed DAG
    // source cannot reach sink ? valid counter-example pair
    cout << "NO\n";
    int a = -1, b = -1;
    for (int i = 1; i <= n; i++) {
        if (comp[i] == num_scc && a == -1) a = i;
        if (comp[i] == 1       && b == -1) b = i;
        if (a != -1 && b != -1) break;
    }
    cout << a << " " << b << "\n";
    return 0;
}
