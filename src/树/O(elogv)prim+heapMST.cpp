const int maxn = int(2e4)+7;
int dist[maxn], head_edge[maxn], cnt_edge;
bitset<maxn> vis;
struct {int next, to, cost;}edge[maxn];
void addedge(int u, int v, int c) {
    edge[cnt_edge] = {head_edge[u], v, c};
    head_edge[u] = cnt_edge++;
}
struct node {
    int u, d;
    bool operator < (const node &tmp) const {
        return d > tmp.d;
    }
}now;
int prim(int cur) {
    int ans = 0, u, v, d;
    vis.reset();
    memset(dist, 0x3f3f3f3f, sizeof(dist));
    priority_queue<node> q;
    q.push({cur, 0});
    dist[cur] = 0;
    while(!q.empty()) {
        now = q.top(), q.pop();
        u = now.u, d = now.d;
        if(vis[u] || d > dist[u]) continue;
        vis[u] = true;
        ans += dist[u];
        for(int i=head_edge[u] ; ~i ; i=edge[i].next) {
            v = edge[i].to;
            if(dist[v] > edge[i].cost) {
                dist[v] = edge[i].cost;
                q.push({v, dist[v]});
            }
        }
    }
    return ans;
}
void init() {
    cnt_edge = 0;
    memset(head_edge, -1, sizeof(head_edge));
}