const int maxn = 1007, INF = 0x3f3f3f3f;
vector<pair<int, int> > edge[maxn];
int m, n, dist[maxn];
bool vis[maxn];

struct cmp {//重载优先队列比较方法
    bool operator () (pair<int, int> y, pair<int, int> x) {//这里第一个是y，第二个是x
        if(x.second == y.second) return x.first < y.first;
        return x.second < y.second;
    }
};

int dijkstra_heap(int start, int end) {//返回从start到end的最短路径
    clr(dist, INF);
    clr(vis, 0);
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> que;
    //以自定义的比较方式创建优先队列
    dist[start] = 0;
    que.push(make_pair(start,0));
    while(!que.empty()) {
        pair<int, int> now = que.top();
        que.pop();
        int u = now.first, v, w;
        if(vis[u]) continue;//每个点只访问一次
        vis[u] = true;
        for(vector<pair<int ,int> >::iterator i=edge[u].begin() ; i!=edge[u].end() ; i++) {
            v = (*i).first, w = (*i).second;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                que.push(make_pair(v, dist[v]));//这里入队的是v和dist[v]，别写错了！
            }
        }
    }
    return dist[end];
}
