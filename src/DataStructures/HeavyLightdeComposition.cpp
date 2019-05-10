// BZOJ-1036: [ZJOI2008]树的统计Count
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=30050;
const int inf=0x3f3f3f3f;
struct Edge
{
    int v,nxt;
}e[maxn*2];
int tot=0;
int w[maxn],h[maxn],n;
void addedge(int x,int y){
    ++tot;
    e[tot].v=y;
    e[tot].nxt=h[x];
    h[x]=tot;
}

int sz[maxn],dep[maxn],fa[maxn],son[maxn];
void dfs1(int x){
    sz[x]=1;
    dep[x]=dep[fa[x]]+1;
    for (int i = h[x]; i ; i=e[i].nxt)
    {
        if(e[i].v!=fa[x]){
            fa[e[i].v]=x;
            dfs1(e[i].v);
            sz[x]+=sz[e[i].v];
            if(sz[e[i].v]>sz[son[x]]) son[x]=e[i].v;
        }
    }
}
int pos[maxn],l=0,idx[maxn],top[maxn];
void dfs2(int x,int chain){
    ++l;
    pos[x]=l;
    idx[l]=x;
    top[x]=chain;
    if(son[x]) dfs2(son[x],chain);
    for (int i = h[x]; i ; i=e[i].nxt)
    {
        if(e[i].v!=fa[x]&&e[i].v!=son[x]){
            dfs2(e[i].v,e[i].v);
        }
    }
}

int mx[maxn*4],sum[maxn*4];
void pushup(int id){
    sum[id]=sum[id*2]+sum[id*2+1];
    mx[id]=max(mx[id*2],mx[id*2+1]);
}
void build(int l,int r,int id){
    if(l==r){
        sum[id]=mx[id]=w[idx[l]];
        return;
    }
    build(l,(l+r)/2,id*2);
    build((l+r)/2+1,r,id*2+1);
    pushup(id);
}
void update(int p,int val,int l,int r,int id){
    if(l==p&&r==p){
        sum[id]=mx[id]=val;
        return ;
    }
    if(p<=(l+r)/2) update(p,val,l,(l+r)/2,id*2);
    else update(p,val,(l+r)/2+1,r,id*2+1);
    pushup(id);
}
int Qsum(int x,int y,int l,int r,int id){
    if(x<=l&&y>=r) return sum[id];
    int ans=0;
    if(x<=(l+r)/2) ans+=Qsum(x,y,l,(l+r)/2,id*2);
    if(y>(l+r)/2) ans+=Qsum(x,y,(l+r)/2+1,r,id*2+1);
    return ans;
}
int Qmax(int x,int y,int l,int r,int id){
    if(x<=l&&y>=r) return mx[id];
    int ans=-inf;
    if(x<=(l+r)/2) ans=max(ans,Qmax(x,y,l,(l+r)/2,id*2));
    if(y>(l+r)/2) ans=max(ans,Qmax(x,y,(l+r)/2+1,r,id*2+1));
    return ans;
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for (int i = 0; i < n-1; ++i)
    {
        int x,y;
        scanf("%d%d", &x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", w+i);
    }
    fa[1]=1;
    dfs1(1);
    dfs2(1,1);
    build(1,n,1);
    // for (int i = 1; i <= n; ++i)
    // {
    //     printf("%d ", Qsum(i,i,1,n,1));
    // }
    // printf("\n");
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        char s[20];
        int x,y;
        scanf("%s %d %d", s,&x,&y);
        if(s[0]=='C') update(pos[x],y,1,n,1);
        else if(s[1]=='M'){
            int ans=-inf;
            while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]]) swap(x,y);
                ans=max(ans,Qmax(pos[top[x]],pos[x],1,n,1));
                x=fa[top[x]];
            // printf("%d\n", ans);
            }
            if(pos[x]>pos[y]) swap(x,y);
            ans=max(ans,Qmax(pos[x],pos[y],1,n,1));
            printf("%d\n", ans);
        }
        else{
            int ans=0;
            while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]]) swap(x,y);
                ans+=Qsum(pos[top[x]],pos[x],1,n,1);
                x=fa[top[x]];
            }
            if(pos[x]>pos[y]) swap(x,y);
            ans+=Qsum(pos[x],pos[y],1,n,1);
            printf("%d\n", ans);
        }
    }
    return 0;
}