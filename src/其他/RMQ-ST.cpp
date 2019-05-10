void init(int n) {//预处理复杂度：O(n*lgn)
    //n为原数组的个数，编号为1~n
    memset(maxq, 0, sizeof maxq);
    for(int i=1 ; i<=n ; i++)
        maxq[i][0] = num[i];
    //bitn为n的二进制位数，取下整(int)(log(n)/log(2))
    int bitn = int(log(double(n))/log(2.0));
    for (int j = 1; j <= bitn; ++j) {
        for (int i = 1; i <= n; ++i) {
            if(i+(1<<(j-1)) > n) break;
            maxq[i][j] = max(maxq[i][j-1], maxq[i+(1<<(j-1))][j-1]);
        }
    }
}
int querymax(int l, int r) {
    int bitn = int(log(double(r-l+1))/log(2.0));
    return max(maxq[l][bitn], maxq[r-(1<<bitn)+1][bitn]);
    //这里注意右区间是r-(1<<bitn)+1，不要忘了加一
}
