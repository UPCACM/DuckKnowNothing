// POJ 1276 每次给你一个承重为 k 的背包，有 n 个物品，每个物品有 x 个，重量为 y ，问最多能装多重的东西
#include <cstdio>
#include <algorithm>
const int maxn = int(1e7) + 7;
int f[maxn];
void ZeroOnePack(int cost, int value, int total) {
    for (int i = total; i >= cost; i--)
        f[i] = std::max(f[i], f[i - cost] + value);
}
void MultiplePack(int cost, int value, int cnt, int total) {
    // 如果总容量比这个物品的容量要小，那么这个物品可以直到取完，相当于完全背包
    if (total <= cnt * cost) {
        for (int i = cost; i <= total; i++)
            f[i] = std::max(f[i], f[i - cost] + value);
    } else { // 否则就将多重背包转化为01背包
        int k = 1;
        while (k <= cnt) {
            ZeroOnePack(k * cost, k * value, total);
            cnt -= k;
            k <<= 1;
        }
        if (cnt) ZeroOnePack(cnt * cost, cnt * value, total);
    }
}
int main() {
    int bag_size, item_num;
    while (~scanf("%d%d", &bag_size, &item_num)) {
        for (int i = 0; i <= bag_size; i++) f[i] = 0;
        for (int i = 0, buf, cnt; i < item_num; i++) {
            scanf("%d%d", &cnt, &buf);
            MultiplePack(buf, buf, cnt, bag_size);
        }
        printf("%d\n", f[bag_size]);
    }
    return 0;
}