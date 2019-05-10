#include <bits/stdc++.h>
using namespace std;
const int maxn = 3000+7, INF = 0x3f3f3f3f;
int dfn[maxn], low[maxn], n, m, result, Time;
//bool cut[maxn][maxn];
vector<pair<int, int> > edge[maxn];
void addedge(int u, int v, int w) {
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
}
void findcut(int u, int pre) {
    dfn[u] = low[u] = Time++;
    for(auto i : edge[u]) {
        int v = i.first, w = i.second;
        if(dfn[v] == -1) {
            findcut(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {
                //cut[u][v] = cut[v][u] = true;
                result = min(result, w);
            }
        }
        else if(pre != v) low[u] = min(low[u], dfn[v]);
    }
}
int main() {
    while(cin >> n >> m) {
        memset(dfn, -1, sizeof dfn);
        result = INF, Time = 1;
        for(int i=0, u, v, w ; i<m ; i++) {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u,v,w);
        }
        for(int i=1 ; i<=n ; i++) if(dfn[i] == -1) findcut(i,i);
        cout << result << '\n';
    }
    return 0;
}
