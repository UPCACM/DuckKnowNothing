/*
    HDU-2665 给你n个数m个询问, 对于每个询问l, r, k, 让你输出区间第k大
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100007;
struct {
    int ls, rs, cnt;
} node[maxn * 20];

int cur, rt[maxn];
inline void init() { cur = 0; }
inline void pushup(int t) {
    node[t].cnt = node[node[t].ls].cnt + node[node[t].rs].cnt;
}
int build(int l, int r) {
    int k = cur++;
    if (l == r) {
        node[k].cnt = 0;
        return k;
    }
    int mid = (l + r) >> 1;
    node[k].ls = build(l, mid);
    node[k].rs = build(mid + 1, r);
    pushup(k);
    return k;
}
int update(int t, int l, int r, int pos, int val) {
    int k = cur++;
    node[k] = node[t];
    if (l == pos && r == pos) {
        node[k].cnt += val;
        return k;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) node[k].ls = update(node[t].ls, l, mid, pos, val);
    else node[k].rs = update(node[t].rs, mid + 1, r, pos, val);
    pushup(k);
    return k;
}
int query(int l, int r, int u, int v, int kth) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int res = node[node[v].ls].cnt - node[node[u].ls].cnt;
    if (kth <= res) return query(l, mid, node[u].ls, node[v].ls, kth);
    else return query(mid + 1, r, node[u].rs, node[v].rs, kth - res);
}

int a[maxn], sorta[maxn], n, m;

int main() {
    int _; scanf("%d", &_);
    while (_--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            sorta[i] = a[i];
        }
        sort(sorta+1, sorta+1+n);
        int cnt = unique(sorta+1, sorta+1+n)-sorta-1;
        rt[0] = build(1, cnt);
        for (int i = 1; i <= n; i++) {
            int p = lower_bound(sorta + 1, sorta + cnt + 1, a[i]) - sorta;
            rt[i] = update(rt[i - 1], 1, cnt, p, 1);
        }
        while(m--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int idx = query(1, cnt, rt[l - 1], rt[r], k);
            printf("%d\n", sorta[idx]);
        }
    }
    return 0;
}