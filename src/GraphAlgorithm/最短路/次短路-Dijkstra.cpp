struct node {
    int u, d;
    node(int u = 0, int d = 0):u(u), d(d) {}
    bool operator < (const node &tmp) const {
        return d > tmp.d;
    }
};
int dijkstra_Secondary(int start, int end) {
    priority_queue<node> que;
    memset(dist, INF, sizeof(dist));
    memset(dist_, INF, sizeof(dist_));
    dist[start] = 0;
    que.emplace(start, dist[start]);
    while(!que.empty()) {
        int u = que.top().u, d_ = que.top().d;
        que.pop();
        if(dist_[u] < d_) continue; //取出的不是次短距离，抛弃
        for(int i = head[u] ; ~i ; i = edge[i].next) {
            int v = edge[i].to, d = d_ + edge[i].val;
            if(dist[v] > d) { //更新最短距离
                swap(dist[v], d);
                que.emplace(v, dist[v]);
            }
            if(dist_[v] > d && dist[v] <= d) {//更新次短距离
                //如果只返回次短路，就删掉上一行的等于号
                dist_[v] = d;
                que.emplace(v, dist_[v]);
            }
        }
    }
    return dist_[end];//如果存在两条最短路，那么返回的就是最短路
}
