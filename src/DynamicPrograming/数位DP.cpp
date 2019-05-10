/*
    HDU-3555 对于每个询问n输出0到n之间含有数字四九的数的个数(1 <= N <= 2^63-1)
*/
#include <bits/stdc++.h>
using namespace std;
long long dp[27][2][2], query;
int bit[27];
long long dfs(int pos, bool four = false, bool nine = false, bool limit = true) {
    if(pos < 0) return nine;
    if(!limit && ~dp[pos][four][nine]) return dp[pos][four][nine];
    int up = limit ? bit[pos] : 9;
    long long ans = 0;
    for(int i=0 ; i<=up ; i++)
        ans += dfs(pos-1, i==4, nine||(four&&i==9), limit&&i==up);
    return limit ? ans : dp[pos][four][nine] = ans;
}
long long solve(long long n) {
    int pos = 0;
    while(n) bit[pos++] = n%10, n/=10;
    return dfs(pos-1);
}
int main() {
    int t; scanf("%d", &t);
    memset(dp, -1, sizeof(dp));
    while(t--) {
        scanf("%lld", &query);
        printf("%lld\n", solve(query));
    }
    return 0;
}