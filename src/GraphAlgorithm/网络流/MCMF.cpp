#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 407, maxm = 15007 << 1, inf = 0x3f3f3f3f;
struct { int next, u, v, flow, cost; } edge[maxm];
struct Graph {
    int head[maxn], cnt;
    Graph() { memset(head, 0xff, sizeof(head)), cnt = 0; }
    void addedge(int u, int v, int flow, int cost) {
        edge[cnt] = {head[u], u, v, flow, cost};
        head[u] = cnt++;
        edge[cnt] = {head[v], v, u, 0, -cost};
        head[v] = cnt++;
    }
} graph;
struct MCMF {
    int dist[maxn], pre[maxn], low[maxn], vis[maxn], que[maxn * maxn], clk;
    bool bfs(int S, int T) {
        vis[S] = ++clk, low[S] = inf, dist[S] = 0, memset(dist, 0x3f, sizeof(dist));
        int head = 0, tail = 0;
        que[tail++] = S;
        while (head < tail) {
            int u = que[head++];
            vis[u] = -1;
            for (int i = graph.head[u]; ~i; i = edge[i].next) {
                int v = edge[i].v, flow = edge[i].flow, cost = edge[i].cost;
                if (dist[v] > dist[u] + cost && flow > 0) {
                    dist[v] = dist[u] + cost;
                    pre[v] = i;
                    low[v] = std::min(low[u], flow);
                    if (vis[v] != clk) {
                        que[tail++] = v;
                        vis[v] = clk;
                    }
                }
            }
        }
        return dist[T] < inf;
    }
    std::pair<ll, ll> solve(int S, int T) {
        ll flow = 0, cost = 0;
        while (bfs(S, T)) {
            flow += low[T];
            cost += 1ll * low[T] * dist[T];
            for (int u = T; u != S; u = edge[pre[u]].u) {
                edge[pre[u]].flow -= low[T];
                edge[pre[u] ^ 1].flow += low[T];
            }
        }
        return std::make_pair(flow, cost);
    }
} mcmf;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, flow, cost; i <= m; i++) {
        scanf("%d%d%d%d", &u, &v, &flow, &cost);
        graph.addedge(u, v, flow, cost);
    }
    std::pair<ll, ll> ans = mcmf.solve(1, n);
    printf("%lld %lld\n", ans.first, ans.second);
    return 0;
}
