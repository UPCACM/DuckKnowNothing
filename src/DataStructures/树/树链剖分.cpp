//bzoj 1036
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <list>
#include <iomanip>
#include <functional>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>

#define read read()
#define edl putchar('\n')
#define clr(a, b) memset(a,b,sizeof(a))
#define rep(i,a,b) for(int i = a ; i<=b ; i++)

using namespace std;

#define lson (i<<1)
#define rson (i<<1|1)

const int maxn = 30007, INF = 0x3f3f3f3f;

struct E {
    int to, next;
}edge[maxn<<1];

int head[maxn], top[maxn], pre[maxn], deep[maxn], sz[maxn], p[maxn], fp[maxn], son[maxn], num[maxn];
int pos, cnt_edge;

void init() {
    cnt_edge = pos = 0;
    clr(head, -1);
    clr(son, -1);
}

void addedge(int u, int v) {
    edge[++cnt_edge] = {v, head[u]};
    head[u] = cnt_edge;
}

void dfs1(int u, int pre_, int d) {
    deep[u] = d;
    pre[u] = pre_;
    sz[u] = 1;
    for(int i = head[u] ; ~i ; i = edge[i].next) {
        int v = edge[i].to;
        if(v != pre_) {
            dfs1(v, u, d+1);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[v] > sz[son[u]]) {
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int sp) { // ???????????????????
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1) return ;
    dfs2(son[u], sp);
    for(int i = head[u] ; ~i ; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != pre[u]) dfs2(v, v);
    }
}

struct {
    int l, r, sum, Max;
}node[maxn<<2];

void pushup(int i) {
    node[i].sum = node[lson].sum + node[rson].sum;
    node[i].Max = max(node[lson].Max, node[rson].Max);
}

void build(int i, int l, int r) {
    node[i].l = l;
    node[i].r = r;
    if(l == r) {
        node[i].sum = node[i].Max = num[fp[l]];
        return ;
    }
    int mid = (l+r)>>1;
    build(lson, l, mid);
    build(rson, mid+1, r);
    pushup(i);
}

void update(int i, int k, int val) {
    if(node[i].l == node[i].r && node[i].l == k) {
        node[i].sum = node[i].Max = val;
        return ;
    }
    int mid = (node[i].l + node[i].r) >> 1;
    if(k <= mid) update(lson, k, val);
    else update(rson, k, val);
    pushup(i);
}

int queryMax(int i, int l, int r) {
    if(node[i].l >= l && node[i].r <= r) {
        return node[i].Max;
    }
    int mid = (node[i].l + node[i].r) >> 1;
    if(r<=mid) return queryMax(lson, l, r);
    if(l > mid) return queryMax(rson, l, r);
    return max(queryMax(lson, l, r), queryMax(rson, l, r));
}

int querySum(int i, int l, int r) {
    if(node[i].l >= l && node[i].r <= r) {
        return node[i].sum;
    }
    int mid = (node[i].l + node[i].r) >> 1;
    if(r<=mid) return querySum(lson, l, r);
    if(l > mid) return querySum(rson, l, r);
    return querySum(lson, l, r) + querySum(rson, l, r);
}

int findMax(int u, int v) { // ?????????????
    int f1 = top[u], f2 = top[v];
    int tmp = -INF;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        cout << f1 << ' ' << u << " | " << p[f1] << ' ' << p[u] << endl;
        tmp = max(tmp, queryMax(1, p[f1], p[u]));
        u = pre[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v]) swap(u, v);
    cout << u << ' ' << v << " | " << p[u] << ' ' << p[v] << endl;
    return max(tmp, queryMax(1, p[u], p[v]));
}

int findSum(int u, int v) { // ??????????????
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp += querySum(1, p[f1], p[u]);
        u = pre[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v]) swap(u, v);
    return tmp + querySum(1, p[u], p[v]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, q, u, v;
    char op[17];
    while(~scanf("%d",&n)) {
        init();
        rep(i,2,n) {
            scanf("%d%d",&u,&v);
            addedge(u, v);
            addedge(v, u);
        }
        rep(i,1,n) scanf("%d",num+i);
        dfs1(1,0,0);
        dfs2(1,1);
        build(1,0,pos-1);
        scanf("%d",&q);
        while(q--) {
            scanf(" %s%d%d", op, &u, &v);
            if(op[0] == 'C') update(1, p[u], v);
            else if(op[1] == 'M') printf("%d\n",findMax(u, v));
            else printf("%d\n",findSum(u,v));
        }
    }
    return 0;
}
