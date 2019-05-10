//单点修改，区间查询
//1.将某个数加上x, 2.求[x, y]区间和
#include <bits/stdc++.h>
const int maxn = int(1e6) + 7;
struct Bit {
    int data[maxn], len;
    inline int lowbit(int x) { return x & -x; }
    void init(int len_) { len = len_, memset(data, 0, sizeof(data)); }
    void add(int pos, int val) { while (pos <= len) data[pos] += val, pos += lowbit(pos); }
    int query(int pos) {
        int ret = 0;
        while (pos) ret += data[pos], pos -= lowbit(pos);
        return ret;
    }
} bit;
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    bit.init(n);
    for (int i = 1, buf; i <= n; i++) scanf("%d", &buf), bit.add(i, buf);
    for (int i = 1, op, x, y; i <= m; i++) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) bit.add(x, y);
        else if (op == 2) printf("%d\n", bit.query(y) - bit.query(x - 1));
    }
    return 0;
}

//区间修改，单点查询
//1.将区间[l, r]中每一个数都加上x, 2.输出第x个数
#include <cstdio>
int n, m, c[500005];
#define lowbit(x) (x&-x)
void add(int pos, int x) { while(pos <= n) c[pos] += x, pos += lowbit(pos);}
int query(int pos) {
    int ans = 0;
    while(pos > 0) ans += c[pos], pos -= lowbit(pos);
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    int x=0, y, op, k;
    for(int i=1 ; i<=n ; i++) scanf("%d",&y), add(i, y-x), x = y;
    while(m--) {
        scanf("%d", &op);
        if(op == 1) scanf("%d%d%d", &x, &y, &k), add(x,k), add(y+1,-k);
        else  scanf("%d", &x), printf("%d\n", query(x));
    }
    return 0;
 }