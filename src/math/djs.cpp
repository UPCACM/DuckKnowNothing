// 计算欧拉函数前缀和模板
// time complexity: O(n^(2/3))
// 需预处理n^(2/3)内的所有答案
unorderd_map<ll,ll> mp;
ll solve(ll n) {
	if(n<N) return phi_sum[n];
	if(mp.count(n)) return mp[n];
	ll nn=n%MOD;
	ll ans=nn*(nn+1)%MOD*inv2%MOD;
	for(ll i = 2; i <= n; ++i) {
		ll t=n/i,nxt=n/t;
		if(nxt>n) nxt=n;
		ans-=(ll)(nxt-i+1)%MOD*solve(t)%MOD;
		i=nxt;
	}
	return mp[n]=ans;
}
