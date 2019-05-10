ll qmul(ll x, ll y, ll mod) {
	x %= mod, y %= mod;
    ll ans = (x * y - (ll)((long double)x / mod * y + 1e-3) * mod);
    ans = (ans % mod + mod) % mod;
    return ans;
}