void ZeroOnePack(int c, int w) {
	for(int i=v ; i>=c ; i--)
		dp[i] = max(dp[i], dp[i-c]+w);
}
void solve() {
	for(int i=0 ; i<n ; i++)
		ZeroOnePack(c[i], w[i]);
}