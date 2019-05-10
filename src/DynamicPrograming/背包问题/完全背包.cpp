void CompletePack(int c, int w) {
	for(int i=0 ; i<=v ; i++) 
		dp[i] = max(dp[i], dp[i-c]+w);
}
void solve() {
	for(int i=0 ; i<n ; i++)
		CompletePack(c[i], w[i]);
}