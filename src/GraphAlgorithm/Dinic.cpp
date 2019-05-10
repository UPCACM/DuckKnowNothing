// 牛客现金最小使用
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const int N = 1e5+50;
struct Edge{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct Dinic{
    int s,t;
    vector<Edge>edges;
    vector<int> G[N];
    bool vis[N];
    int d[N];
    int cur[N];
    void init(){
       for (int i=0;i<=t+1;i++)
           G[i].clear();
       edges.clear();
    }
    void AddEdge(int from,int to,int cap){
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        int mm=edges.size();
        G[from].push_back(mm-2);
        G[to].push_back(mm-1);
    }
    bool BFS(){
        memset(vis,0,sizeof(vis));
        queue<int>q;
        q.push(s);
        d[s]=0;
        vis[s]=1;
        while (!q.empty()){
            int x = q.front();q.pop();
            for (int i = 0;i<G[x].size();i++){
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow){
                    vis[e.to]=1;
                    d[e.to] = d[x]+1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
 
    int DFS(int x,int a) {
        if (x==t || a==0)
            return a;
        int flow = 0,f;
        for(int &i=cur[x];i<G[x].size();i++){
            Edge &e = edges[G[x][i]];
            if (d[x]+1 == d[e.to] && (f=DFS(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if (a==0)
                    break;
            }
        }
        return flow;
    }
 
    int Maxflow(int s,int t){
        this->s=s;
        this->t=t;
        int flow = 0;
        while (BFS()){
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,inf);
        }
        return flow;
    }
}dc;
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n,m;
        scanf("%d%d",&n,&m);
        int s=n+m+1,t=n+m+2;
        dc.init();
        int sum=0;
        for (int i = 1; i <= n; ++i)
        {
            int x;
            scanf("%d", &x);
            sum+=x;
            dc.AddEdge(i,t,x);
        }
        for (int i = n+1; i <= n+m; ++i)
        {
            int x;
            scanf("%d", &x);
            dc.AddEdge(s,i,x);
        }
        for (int i = n+1; i <= n+m; ++i)
        {
            int k;
            scanf("%d", &k);
            while(k--){
                int x;
                scanf("%d", &x);
                dc.AddEdge(i,x,inf);
            }
        }
        printf("%d\n", sum-dc.Maxflow(s,t));
    }
    return 0;
}
