const int maxn = 105, INF = 0x3f3f3f3f;
int map[maxn][maxn], dist[maxn];
bool inque[maxn];
int n, m;
int spfa(int n, int start) {
    clr(dist, INF);
    clr(inque, 0);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    inque[start] = true;
    while(!q.empty()) {
        int index = q.front();
        q.pop();
        for(int i=1 ; i<=n ; i++)
            if(dist[i] > dist[index] + mp[index][i]) {
                dist[i] = dist[index] + mp[index][i];
                if(!inque[i]) {
                    q.push(i);
                    inque[i] = true;
                }
            }
        inque[index] = false;
    }
    return dist[n];
}