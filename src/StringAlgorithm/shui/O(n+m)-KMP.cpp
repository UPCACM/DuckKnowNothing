#include <bits/stdc++.h>
const int maxn = int(2e7)+7;
struct KMP {
    int next[maxn];  // next下表:[0, strlen(p)]
    int process(const char *p) {
        int i = 0, j = next[0] = -1, m = int(strlen(p));
        while (i < m) {
            if (j < 0 || p[i] == p[j]) {
                i++, j++;
                next[i] = (p[i] == p[j] ? next[j] : j);
                // next[i] = j;  // 求循环节的时候需要这样写，对于字符串中的第i个位置
                // 如果i % (i - next[i]) == 0，最小循环节长度为i - next[i] (i >= 1)
            } else j = next[j];
        }
        return m;
    }
    int kmp(const char *str, const char *p) {  // s:匹配串 p:模式串, 下标均从0开始
        int i = 0, j = 0, n = int(strlen(str)), m = int(strlen(p));
        // int cnt = 0;  //  p串出现的次数
        while (i < n && j < m) {
            if (j < 0 || str[i] == p[j]) i++, j++;
            else j = next[j];
            if(j == m) {
                return i - m;  // 返回第一次出现的下标，从0开始
                // j = next[j], cnt++;  // 可重叠出现次数
                // j = 0, cnt++;  // 不可重叠出现次数
            }
        }
        return -1;
        // return cnt;
    }
} kmp;
char p[maxn], s[maxn];
int main() {
    std::cin >> s >> p;
    kmp.process(p);
    std::cout << kmp.kmp(s, p) << std::endl;
    return 0;
}
