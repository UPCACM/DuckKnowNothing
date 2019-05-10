#include <iostream>
#include <vector>
using namespace std;
const int maxn = int(1e5)+7;

vector<int> edge[maxn];
int tim,tp[maxn],n,m;
bool vis[maxn],in[maxn];

void dfs(int u) {
    vis[u] = true;
    for(auto v : edge[u]) if(!vis[v]) dfs(v);
    tp[tim--] = u;
}

void topological_sort() {
    tim = n;
    for(int i=1 ; i<=n ; i++) if(!vis[i]) dfs(i);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i=0, u, v ; i<m ; i++) {
        cin >> u >> v;
        in[v]=true;
        edge[u].push_back(v);
    }
    topological_sort();
    for(int i=1 ; i<n ; i++) cout << tp[i] << ", ";
    cout << tp[n];
    return 0;
}
