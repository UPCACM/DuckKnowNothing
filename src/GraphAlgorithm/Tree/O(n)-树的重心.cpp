// POJ 1655 给定一棵树，求树的重心的编号以及重心删除后得到的最大子树的节点个数，如果个数相同就选取编号最小的。
/*
 * 1.树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么他们的距离和一样。
 * 2.把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两个树的重心的路径上。
 * 3.在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。
 */
#include <cstdio>
#include <algorithm>
#include <vector>
const int maxn = int(1e5) + 7;
int cnt[maxn], n, t;
struct { int index, cnt; } ans{0, 0x3f3f3f3f};
std::vector<int> edge[maxn];
void dfs(int u, int pre = -1) {
    cnt[u] = 1;
    int max = 0, len = int(edge[u].size());
    for (int i = 0; i < len; i++) {
        int v = edge[u][i];
        if (v == pre) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
        max = std::max(max, cnt[v]);
    }
    max = std::max(max, n - cnt[u]);
    if (max < ans.cnt || (max == ans.cnt && u < ans.index)) {
        ans.cnt = max;
        ans.index = u;
    }
}
void init() {
    ans.index = 0, ans.cnt = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) edge[i].clear();
}
int main() {
    for (scanf("%d", &t); t; t--) {
        init();
        scanf("%d", &n);
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1);
        printf("%d %d\n", ans.index, ans.cnt);
    }
    return 0;
}