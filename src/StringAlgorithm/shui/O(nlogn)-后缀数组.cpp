#include <bits/stdc++.h>
const int maxn = int(1e6) + 7;
namespace DA {  // sa[i]代表排名第i的后缀的下标, height[i]代表相邻排名的最长公共前缀
    int base[maxn], tmp[maxn], sa[maxn], rank[maxn], height[maxn];  // 下标均从1开始
    bool cmp(const int *s, int u, int v, int l, int n) {
        return s[u] == s[v] && (u + l > n ? 0 : s[u + l]) == (v + l > n ? 0 : s[v + l]);
    }  // 注意是大于s
    void clear(int m) { for (int i = 1; i <= m; i++) base[i] = 0; }
    void init(const char *s, int n, int m) { // 注意字符集的最小值应该从1开始
        int i, k = 0, *pre = rank, *cur = height;
        for (i = 1, clear(m); i <= n; i++) base[pre[i] = s[i]]++;
        for (i = 2; i <= m; i++) base[i] += base[i - 1];
        for (i = n; i; i--) sa[base[pre[i]]--] = i;
        for (int l = 1, p = 1; p < n && l <= n; l <<= 1, m = p) {
            for (p = 0, i = n - l + 1; i <= n; i++) cur[++p] = i;
            for (i = 1; i <= n; i++) if (sa[i] > l) cur[++p] = sa[i] - l;
            for (i = 1; i <= n; i++) tmp[i] = pre[cur[i]];
            for (i = 1, clear(m); i <= n; i++) base[tmp[i]]++;
            for (i = 2; i <= m; i++) base[i] += base[i - 1];
            for (i = n; i; i--) sa[base[tmp[i]]--] = cur[i];
            for (std::swap(pre, cur), p = 1, pre[sa[1]] = 1, i = 2; i <= n; i++)
                pre[sa[i]] = cmp(cur, sa[i - 1], sa[i], l, n) ? p : ++p;
        }  // pre[sa[1]] = 1, 不要敲错
        for (i = 1; i <= n; i++) rank[sa[i]] = i;
        for (i = 1; i <= n; height[rank[i++]] = k)  // height[rank[i]] = k, i++
            for (k ? k-- : 0; s[i + k] == s[sa[rank[i] - 1] + k]; k++);
    }
}
char str[maxn];
int main() {
    while (~scanf("%s", str + 1)) {
        int len = int(strlen(str + 1));
        DA::solve(str, len, 130);
        puts("------------------Sa------------------");
        for (int i = 1; i <= len; ++i) printf("sa[%2d ] = %2d\t%s\n", i, DA::sa[i], str + DA::sa[i]);
        puts("---------------Height-----------------");
        for (int i = 1; i <= len; ++i) printf("height[%2d ]= %2d \n", i, DA::height[i]);
        puts("----------------rank------------------");
        for (int i = 1; i <= len; ++i) printf("rank[%2d ] = %2d\n", i, DA::rank[i]);
        puts("------------------END-----------------");
    }
    return 0;
}