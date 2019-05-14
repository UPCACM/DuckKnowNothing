#include <bits/stdc++.h>
const int maxn = int(1e5) + 7, maxm = int(4e5) + 7;
struct Lca { // 点的下标从1开始
    int dep[maxn], up[maxn][32], cnt, head[maxn];
    struct { int next, to, val; } edge[maxm];
    void addedge(int u, int v, int w) {
        edge[cnt] = {head[u], v, w};
        head[u] = cnt++;
    }
    Lca() {
        cnt = 0;
        memset(head, 0xff, sizeof(head));
        memset(up, 0xff, sizeof(up));
    }
    void init(int n) {
        std::queue<int> que;
        que.emplace(dep[1] = 1); // 下标从1开始
        int u, v;
        while (!que.empty()) {
            u = que.front(), que.pop();
            for (int i = head[u]; ~i; i = edge[i].next) {
                v = edge[i].to;
                if (dep[v]) continue ;
                up[v][0] = u, dep[v] = dep[u] + 1, que.push(v);
            }
        }
        for (int j = 1; j <= 20; j++)
            for (int i = 1; i <= n; i++)
                if (~up[i][j - 1])
                    up[i][j] = up[up[i][j - 1]][j - 1];
    }
    int query(int u, int v) {
        if (dep[u] < dep[v]) std::swap(u, v);
        int tmp = dep[u] - dep[v];
        for (int j = 0; tmp; j++)
            if (tmp & (1 << j)) tmp ^= (1 << j), u = up[u][j];
        if (u == v) return v;
        for (int j = 20; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j], v = up[v][j];
            }
        }
        return up[u][0];
    }
} lca;