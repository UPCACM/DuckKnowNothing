struct BitTree {
    int data[307][307];
    void update(int x, int y, int w) { //将点(x, y)加上w
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                data[i][j] += w;
    }
    int query(int x, int y) { //求左上角为(1,1)右下角为(x,y) 的矩阵和
        int ret = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                ret += data[i][j];
        return ret;
    }
};