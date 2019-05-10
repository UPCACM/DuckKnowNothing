void CompletePack(int c, int w) {
	for(int i=0 ; i<=v ; i++) 
		dp[i] = max(dp[i], dp[i-c]+w);
}
void ZeroOnePack(int c, int w) {
	for(int i=v ; i>=c ; i--)
		dp[i] = max(dp[i], dp[i-c]+w);
}
void MultiplePack(int c,int w,int cnt) {
	//如果总容量比这个物品的容量要小，那么这个物品可以直到取完，相当于完全背包
    if(v<=cnt*c) CompletePack(c, w);
    else {//否则就将多重背包转化为01背包
        int k = 1;
        while(k<cnt) {
            ZeroOnePack(k*c, k*w);
            cnt = cnt-k;
            k<<=1;
        }
        if(cnt) ZeroOnePack(cnt*cost, cnt*wei);
    }
}