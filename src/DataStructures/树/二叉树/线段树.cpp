#include <bits/stdc++.h>

const int maxn = int(2e5) + 7;
namespace SegmentTree {
#define ls (t << 1)
#define rs (t << 1 | 1)
    int len;  // 线段树的区间长度，下标从1开始
    typedef int type;
    type *buf;

    class SgmtTree {
    private:
        type node[maxn << 2], laz[maxn << 2];  //node是树节点，laz是lazy标记
        void pushdown(int t, int l, int r) {
            int mid = (l + r) >> 1;
            laz[ls] += laz[t];
            laz[rs] += laz[t];
            node[ls] += laz[t] * (mid - l + 1);
            node[rs] += laz[t] * (r - mid);
            laz[t] = 0;
        }

        void pushup(int t) {
            node[t] = node[ls] + node[rs];
        }

        void build(int t = 1, int l = 1, int r = len) {
            if (l == r) {
                node[t] = buf[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            pushup(t);
        }

    public:
        void init(type *tmp, int len_) {  // 用长度为len_的数组tmp去初始化线段树
            len = len_;
            buf = tmp;
            memset(laz, 0, sizeof(laz));
            build(1, 1, len);  // 下标从1开始
        }

        void update(int b, int e, type num, int t = 1, int l = 1, int r = len) {
            if (e < l || b > r) return;
            if (b <= l && r <= e) {
                laz[t] += num;
                node[t] += num * (r - l + 1);
                return;
            }
            if (laz[t]) pushdown(t, l, r);
            int mid = (l + r) >> 1;
            update(b, e, num, ls, l, mid);
            update(b, e, num, rs, mid + 1, r);
            pushup(t);
        }

        type query(int b, int e, int t = 1, int l = 1, int r = len) {
            if (e < l || b > r) return type(0);
            if (b <= l && r <= e) return node[t];
            if (laz[t]) pushdown(t, l, r);
            int mid = (l + r) >> 1;
            if (e <= mid) query(b, e, ls, l, mid);
            if (b > mid) query(b, e, rs, mid + 1, r);
            return query(b, e, ls, l, mid) + query(b, e, rs, mid + 1, r);
        }
    } tree;
} using SegmentTree::tree;

int a[maxn], len = 5;

int main() {
    for (int i = 1; i <= len; i++) a[i] = 1;
    tree.init(a, len); // 初始化线段树，下标从1开始
    std::cout << tree.query(1, len) << std::endl; // 查询区间和
    tree.update(1, len, 1); // 区间[1, len]加一
    std::cout << tree.query(1, len) << std::endl;
    return 0;
}