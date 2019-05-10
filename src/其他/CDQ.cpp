// luogu3810 求满足x<=a,y<=b,z<=c的点的个数
// time complexity: O(nlog^2(n))
#include <bit/stdc++.h>
using namespace std;
const int maxn=100050;
struct node {
    int x,y,z,w;
    int sum;
    void read() {
        scanf("%d%d%d", &x,&y,&z);
    }
    bool operator <(const node&t)const {
        if(x!=t.x) return x<t.x;
        if(y!=t.y) return y<t.y;
        return z<t.z;
    }
    bool operator !=(const node&t)const {
        return x!=t.x||y!=t.y||z!=t.z;
    }
}a[maxn],t[maxn];
int M,n;
bool cmpy(const node&a,const node&t) {
    return a.y<t.y;
}
int sum[maxn*2];
void add(int x,int val) {
    while(x<=M) {
        sum[x]+=val;
        x+=(x&-x);
    }
}
int query(int x) {
    int ans=0;
    while(x) {
        ans+=sum[x];
        x-=(x&-x);
    }
    return ans;
}
void solve(int l,int r) {
    if(l==r) return;
    int mid=(l+r)>>1;
    solve(l,mid),solve(mid+1,r);
    // sort(a+l,a+mid+1,cmpy),sort(a+mid+1,a+r+1,cmpy);
    int p=l;
    for(int i = mid+1; i <= r; ++i) {
        while(p<=mid&&a[p].y<=a[i].y) add(a[p].z,a[p].w),++p;
        a[i].sum+=query(a[i].z);
    }
    for(int i = l; i < p; ++i) add(a[i].z,-a[i].w);
    merge(a+l,a+mid+1,a+mid+1,a+r+1,t,cmpy);
    for(int i = l; i <= r; ++i) a[i]=t[i-l];
}
int ans[maxn];
int main() {
    scanf("%d%d", &n,&M);
    int n0=n;
    for(int i = 1; i <= n; ++i) {
        a[i].read();
    }
    sort(a+1,a+1+n);
    int tot=0;
    for(int i = 1; i <= n; ++i) {
        if(!tot||t[tot]!=a[i]) t[++tot]=a[i],t[tot].w=1;
        else t[tot].w++;
    }
    swap(a,t);
    n=tot;
    solve(1,n);
    for(int i = 1; i <= n; ++i) {
        ans[a[i].sum+a[i].w-1]+=a[i].w;
    }
    for(int i = 0; i < n0; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}