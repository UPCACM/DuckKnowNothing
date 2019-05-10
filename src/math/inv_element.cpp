// 利用exgcd，必须满足a与mod互质才存在a的逆元
ll inv_ele(ll a,ll mod){
	ll x,y;
	ll d=exgcd(a,mod,x,y);
	if(d==1) return (x+mod)%mod;
	return -1;
}

// 利用Pow(a,mod-2)必须满足mod为质数


// 线性时间求逆元
ll inv[maxn];
void init()
{
    inv[1]=1;
    for(int i = 2; i < maxn; ++i) inv[i]=(-MOD/i+MOD)*inv[MOD%i]%MOD;
}