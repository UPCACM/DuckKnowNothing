// exam7036 查询区间最大的h,使得至少h个数不小于h
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=100050;
int n,q,a[maxn];
int sz,sum[maxn*20],lson[maxn*20],rson[maxn*20];
int update(int x,int l,int r,int id){
    int root=++sz;
    if(l==x&&r==x){
        sum[root]=sum[id]+1;
        lson[root]=rson[root]=0;
        return root;
    }
    int mid=(l+r)>>1;
    if(x<=mid){
        lson[root]=update(x,l,mid,lson[id]);
        rson[root]=rson[id];
    }
    else{
        lson[root]=lson[id];
        rson[root]=update(x,mid+1,r,rson[id]);
    }
    sum[root]=sum[lson[root]]+sum[rson[root]];
    return root;
}
int query(int suf,int l,int r,int r1,int r2){
    if(l==r){
        return l;
    }
    int s=sum[rson[r2]]-sum[rson[r1]];
    int mid=(l+r)>>1;
    if(s+suf>=mid+1) return query(suf,mid+1,r,rson[r1],rson[r2]);
    else return query(s+suf,l,mid,lson[r1],lson[r2]);
}
int T[maxn];
int main(int argc, char const *argv[])
{
    while(~scanf("%d%d", &n,&q)){
        T[0]=0;
        sz=0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
            T[i]=update(a[i],1,n,T[i-1]);
        }
        while(q--){
            int l,r;
            scanf("%d%d", &l,&r);
            printf("%d\n", query(0,1,n,T[l-1],T[r]));
        }
    }
    return 0;
}