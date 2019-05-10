#include <bits/stdc++.h>
const int maxn = 1007, maxm = int(4e6) + 7, inf = 0x3f3f3f3f;
struct { int next, v, flow; } edge[maxm << 1];
struct Graph {
    int head[maxn], cnt;
    Graph() { memset(head, 0xff, sizeof(head)), cnt = 0; }
    void addedge(int u, int v, int flow) {
        edge[cnt] = {head[u], v, flow};
        head[u] = cnt++;
        edge[cnt] = {head[v], u, 0};
        head[v] = cnt++;
    }
} graph;
struct Dinic {
    int dist[maxn], cur[maxn], que[maxn * maxn];
    bool bfs(int S, int T) {
        memset(dist, 0xff, sizeof(dist));
        dist[S] = 0;
        int head = 0, tail = 0;
        que[tail++] = S;
        while (head < tail) {
            int u = que[head++];
            for (int i = graph.head[u]; ~i; i = edge[i].next) {
                int v = edge[i].v, flow = edge[i].flow;
                if (dist[v] == -1 && flow > 0) {
                    dist[v] = dist[u] + 1;
                    if (v == T) return true;
                    que[tail++] = v;
                }
            }
        }
        return false;
    }
    int dfs(int u, int low, int T) {
        if (u == T) return low;
        for (int &i = cur[u]; ~i; i = edge[i].next) {
            int v = edge[i].v, flow = edge[i].flow;
            if (dist[v] == dist[u] + 1 && flow > 0) {
                int min = dfs(v, flow < low ? flow : low, T);
                if (min > 0) {
                    edge[i].flow -= min;
                    edge[i ^ 1].flow += min;
                    return min;
                }
            }
        }
        return 0;
    }
    int solve(int S, int T) {
        int ans = 0, tmp;
        while (bfs(S, T)) {
            memcpy(cur, graph.head, sizeof(cur));
            while (tmp = dfs(S, inf, T), tmp > 0) ans += tmp;
        }
        return ans;
    }
} dinic;
int main() {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0, u, v, flow; i < m; i++) {
        scanf("%d%d%d", &u, &v, &flow);
        graph.addedge(u, v, flow);
    }
    printf("%d\n", dinic.solve(s, t));
    return 0;
}