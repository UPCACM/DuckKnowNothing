// 18位素数：154590409516822759
// 19位素数：2305843009213693951 (梅森素数)
// 19位素数：4384957924686954497
typedef long long ll;
struct Miller_Rabin
{
    int prime[5]={2,3,5,233,331};
    ll qmul(ll x,ll y,ll mod){
        x%=mod,y%=mod;
        ll ans=(x*y-(ll)((long double)x/mod*y+1e-3)*mod);
        ans=(ans%mod+mod)%mod;
        return ans;
    }
    ll qpow(ll x,ll n,ll mod){
        ll ans=1;
        while(n){
            if(n&1) ans=qmul(ans,x,mod);
            x=qmul(x,x,mod);
            n>>=1;
        }
        return ans;
    }
    bool isprime_std(ll p) {
        if(p < 2) return 0;
        if(p != 2 && p % 2 == 0) return 0;
        ll s = p - 1;
        while(! (s & 1)) s >>= 1;
        for(int i = 0; i < 5; ++i) {
            if(p == prime[i]) return 1;
            ll t = s, m = qpow(prime[i], s, p);
            while(t != p - 1 && m != 1 && m != p - 1) {
                m = qmul(m, m, p);
                t <<= 1;
            }
            if(m != p - 1 && !(t & 1)) return 0;
        }
        return 1;
    }
};
