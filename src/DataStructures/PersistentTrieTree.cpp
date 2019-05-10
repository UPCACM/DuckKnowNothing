#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=50050;
int ch[maxn*20][2],sz=0;
int val[maxn*20],root[maxn];
void insert(int pos,int x){
    int l=root[pos-1],r=++sz;
    root[pos]=sz;
    for (int i = 15; i >= 0; --i)
    {
        ch[r][0]=ch[l][0];
        ch[r][1]=ch[l][1];
        val[r]=pos;
        ch[r][(x>>i)&1]=++sz;
        r=ch[r][(x>>i)&1];
        l=ch[l][(x>>i)&1];
    }
    val[r]=pos;
}
int query(int l,int r,int x){
    int ans=0,u=root[r];
    for (int i = 15; i >= 0; --i)
    {
        // printf("%d %d %d\n", i,x,ch[u][(x>>i)&1^1]);
        if(val[ch[u][(x>>i)&1^1]]>=l) u=ch[u][(x>>i)&1^1],ans|=(1<<i);
        else if(val[ch[u][(x>>i)&1]]>=l) u=ch[u][(x>>i)&1];
        else break;
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    int n,m;
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        insert(i,x);
    }
    for (int i = 0; i < m; ++i)
    {
        int l,r,x;
        scanf("%d%d%d", &l,&r,&x);
        printf("%d\n", query(l,r,x));
    }
    return 0;
}
/**************************************************************
    Problem: 5679
    User: upc_reserver201706
    Language: C++
    Result: 正确
    Time:76 ms
    Memory:13624 kb
****************************************************************/