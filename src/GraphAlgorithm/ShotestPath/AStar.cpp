#include <bits/stdc++.h>
const int maxn = int(1e4) + 7, maxm = int(1e5) + 7, inf = 0x3f3f3f3f;
int n, m, k, t, S, T, f[maxn];
struct Graph {
    int head[maxn], cnt;
    struct { int next, v, cost; } edge[maxm];
    void init() {
        memset(head, 0xff, sizeof(head));
        cnt = 0;
    }
    void addedge(int u, int v, int cost) {
        edge[cnt] = {head[u], v, cost};
        head[u] = cnt++;
    }
} graph, inv;
struct Node {
    int index, cost, dist;
    Node(int index, int dist, int cost = 0):index(index), dist(dist), cost(cost) {}
    bool operator < (const Node &tmp) const {
        return dist + cost > tmp.dist + tmp.cost;
    }
};
void bfs(int S, const Graph &g) {
    std::bitset<maxn> vis;
    std::priority_queue<Node> que;
    memset(f, 0x3f, sizeof(f));
    f[S] = 0;
    que.emplace(S, 0);
    while (!que.empty()) {
        Node cur = que.top();
        que.pop();
        int u = cur.index;
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = g.head[u]; ~i; i = g.edge[i].next) {
            int v = g.edge[i].v, cost = g.edge[i].cost;
            if (f[v] > f[u] + cost) {
                f[v] = f[u] + cost;
                if (!vis[v]) que.emplace(v, f[v]);
            }
        }
    }
}

int Astar(int S, int T, int k, const Graph &g) {
    bfs(T, inv);
    int cnt[maxn] = {0};
    std::priority_queue<Node> que;
    que.emplace(S, 0, f[S]);
    while (!que.empty()) {
        Node cur = que.top();
        que.pop();
        int u = cur.index;
        if (++cnt[u] > k) continue;
        if (u == T && cnt[u] == k) return cur.dist;
        if(cur.dist >= t) return inf;
        for (int i = g.head[u]; ~i; i = g.edge[i].next) {
            int v = g.edge[i].v, cost = g.edge[i].cost;
            if (cnt[v] < k) que.emplace(v, cur.dist + cost, f[v]);
        }
    }
    return inf;
}
int main() {
    while (graph.init(), inv.init(), ~scanf("%d%d", &n, &m)) {
        scanf("%d%d%d%d", &S, &T, &k, &t);
        for (int i = 1, u, v, cost; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &cost);
            graph.addedge(u, v, cost);
            inv.addedge(v, u, cost);
        }
        puts(Astar(S, T, k, graph) <= t ? "yareyaredawa" : "Whitesnake!");
    }
    return 0;
}