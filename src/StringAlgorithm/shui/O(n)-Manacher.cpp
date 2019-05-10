#include <bits/stdc++.h>
const int maxn = int(1e6) + 7;
int p[maxn << 1]; // p[i] 在增广串中以i为中心的最长回文串的半径，半径长度包括str[i]本身
int Manacher(char *str) {
    int len = int(strlen(str)), max_len = -1; // max_len 最长回文串的长度
    int max_right = 0, pos = 0; // max_right 当前已访问过的所有回文串能触及的最右端的下标
    for (int i = len; i >= 0; i--) str[i + i + 2] = str[i], str[i + i + 1] = '#';
    str[0] = '$'; // 下标是从1开始的
    for (int i = 1; str[i]; i++) {
        p[i] = (max_right > i ? std::min(p[pos + pos - i], max_right - i) : 1);
        while (str[i + p[i]] == str[i - p[i]]) p[i]++;
        if (max_right < i + p[i]) pos = i, max_right = i + p[i];
        max_len = std::max(max_len, p[i] - 1);
    }
    return max_len;
}
char str[maxn << 1]; // 字符串长度要两倍于原串
int main() {
    std::cin >> str;
    std::cout << Manacher(str) << std::endl;
    return 0;
}