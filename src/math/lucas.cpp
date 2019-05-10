// 需要预处理出min(n,p-1) 以内的阶乘和阶乘的逆元
// time complexity: O(log(n)/log(p)+min(n,p));
ll fact[maxn],inv[maxn],p;
ll C(int n,int k) {
	if(k>n||k<0) return 0;
	assert(n<p&&k<p);
	return fact[n]*inv[k]%p*inv[n-k]%p;
}
ll lucas(int n,int k) {
	if(k>n||k<0) return 0;
	if(!k) return 1;
	return C(n%p,k%p)*lucas(n/p,k/p)%p;
}
