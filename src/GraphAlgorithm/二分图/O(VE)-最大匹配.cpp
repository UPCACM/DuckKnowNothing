//跑有向图的时候得保证所有的边都满足从集合S指向集合T
const int maxn = 207;
struct {
    int next, to;
}edge[maxn * maxn];
int head_edge[maxn * maxn], cnt_edge;
int n, link[maxn];
bool vis[maxn];

void addedge(int u, int v) {
    edge[cnt_edge] = {head_edge[u], v};
    head_edge[u] = cnt_edge++;
}

bool dfs(int u) {
    for(int i = head_edge[u] ; ~i ; i = edge[i].next) {
        int v = edge[i].to;
        if(vis[v]) continue;
        vis[v] = true;
        if(link[v] == -1 || dfs(link[v])) {
            link[v] = u;
            link[u] = v;
            return true;
        }
    }
    return false;
}

int match() {
    int ans = 0;
    clr(link, -1);
    for (int i = 1; i <= n; i++)
        if (link[i] == -1) {
            clr(vis, 0);
            if (dfs(i)) ans++;
        }
    return ans;
}

void init() {
    clr(head_edge, -1);
    cnt_edge = 0；
}