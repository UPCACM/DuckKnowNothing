typedef long long ll;
ll tab[6] = {2, 3, 5, 233, 331};
ll qmul(ll x, ll y, ll mod) {
    return (x * y - (long long)(x / (long double)mod * y + 1e-3) *mod + mod) % mod;
}
ll qpow(ll a, ll n, ll mod) {
    ll ret = 1;
    while(n) {
        if(n & 1) ret = qmul(ret, a, mod);
        a = qmul(a, a, mod);
        n >>= 1;
    }
    return ret;
}
bool Miller_Rabin(ll p) {
    if(p < 2) return false;
    if(p != 2 && p % 2 == 0) return false;
    ll s = p - 1;
    while(! (s & 1)) s >>= 1;
    for(int i = 0; i < 5; ++i) {
        if(p == tab[i]) return true;
        ll t = s, m = qpow(tab[i], s, p);
        while(t != p - 1 && m != 1 && m != p - 1) {
            m = qmul(m, m, p);
            t <<= 1;
        }
        if(m != p - 1 && !(t & 1)) return false;
    }
    return true;
}

bool isPrime(ll n) { return Miller_Rabin(n); }