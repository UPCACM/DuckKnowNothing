//poj 1986
#include <bits/stdc++.h>
#define read read()
#define edl putchar('\n')
#define clr(a,b) memset(a,b,sizeof a)
int read{ int x=0;char c=getchar();while(c<'0' || c>'9')c=getchar();while(c>='0' && c<='9'){ x=x*10+c-'0';c=getchar(); }return x;}
void write(int x){ int y=10,len=1;while(y<=x)   {y*=10;len++;}while(len--){y/=10;putchar(x/y+48);x%=y;}}
using namespace std;

const int maxn = int(1e5)+7;
int n,m,k,ans[maxn],cnt;

int pre[maxn];
int find(int x) { return (pre[x] == x ? x : pre[x] = find(pre[x])); }

vector<pair<int,int> > edge[maxn], query[maxn];
void addedge(int u, int v, int w) {
    edge[u].push_back(make_pair(v,w));
    edge[v].push_back(make_pair(u,w));
}

void add(int f, int s) {
    int ff = find(f), fs = find(s);
    if(ff == fs) return ;
    pre[fs] = ff;
}

int cost[maxn];
bool vis[maxn];
void tarjan(int u, int p) {
    int len = int(edge[u].size());
    for(int i=0, v, w ; i<len ; i++) {
        v = edge[u][i].first, w = edge[u][i].second;
        if (v == p) continue;
        cost[v] = cost[u] + w;
        tarjan(v, u);
        add(u, v);
    }
    vis[u] = true;
    if(cnt == k) return ;
    int lenq = int(query[u].size());
    for(int i=0 ; i<lenq ; i++) {
        int v = query[u][i].first;
        if(vis[v]) {
            ans[query[u][i].second] = cost[u] + cost[v] - 2 * cost[find(v)];
        }
    }
}

void init() {
    for(int i=1 ; i<=n ; i++) {
        pre[i] = i;
        edge[i].clear();
        query[i].clear();
    }
    cnt = 0;
    clr(vis,0);
    clr(cost,0);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(cin >> n >> m) {
        init();
        for(int i=0, u, v, w ; i<m ; i++) {
            u = read, v = read, w = read;
            addedge(u,v,w);
        }
        k = read;
        for(int i=0, u, v ; i<k ; i++) {
            u = read, v = read;
            query[u].push_back(make_pair(v,i));
            query[v].push_back(make_pair(u,i));
            ans[i] = 0;
        }
        tarjan(1,0);
        for(int i=0 ; i<k ; i++) write(ans[i]),edl;
    }
    return 0;
}
