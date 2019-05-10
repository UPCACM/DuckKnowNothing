#include <bits/stdc++.h>
using namespace std;
const int maxn=1050;
struct Hungarian
{
    vector<int> G[maxn];
    void addEdge(int x,int y)
    {
        G[x].push_back(y);
        G[y].push_back(x);
    }
    int n,mat[maxn];
    bool vis[maxn];
    void init(int _n)
    {
        n=_n;
        for(int i = 1; i <= n; ++i)
            G[i].clear(),vis[i]=mat[i]=0;
    }
    int maxMatch()
    {
        int ans=0;
        for(int i = 1; i <= n; ++i)
        {
            if(mat[i]) continue;
            memset(vis,false,sizeof vis);
            if(match(i)) ans++;
        }
        return ans;
    }
    bool match(int x)
    {
        if(vis[x]) return false;
        vis[x]=true;
        for(auto y:G[x])
        {
            if(vis[y]) continue;
            if(mat[y]==0||match(mat[y]))
            {
                mat[y]=x;
                mat[x]=y;
                return true;
            }
        }
        return false;
    }
}s;
int n,m;
int main()
{
    scanf("%d%d", &n,&m);
    s.init(n);
    for(int i = 0; i < m; ++i)
    {
        int x,y;
        scanf("%d%d", &x,&y);
        s.addEdge(x,y);
    }
    printf("%d\n", s.maxMatch());
    return 0;
}
