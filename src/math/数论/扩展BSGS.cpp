#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
map<ll, ll> mp;
ll power(ll p, ll q, ll c) {
    ll ans = 1;
    while (q) {
        if (q & 1) ans = ans * p % c;
        q >>= 1;
        p = p * p % c;
    }
    return ans;
}

ll gcd(ll a, ll b) { return (b) ? gcd(b, a % b) : a; }

// 求解使得a^x == b (Mod c)的最小非负整数x

inline int EX_BSGS(ll a, ll b, ll p) {
    if (p == 1) return 0 * puts("0");
    a %= p, b %= p;
    if (!a && !b) return 0 * puts("1");
    if (b == 1) return 0 * puts("0");
    if (!a) return 0 * puts("No Solution");
    ll d, step = 0, k = 1;
    while ((d = gcd(a, p)) != 1) {
        if (b % d) return 0 * puts("No Solution");
        step++;
        p /= d, b /= d, k = k * a / d % p;
        if (b == k) return 0 * printf("%lld\n", step);
    }
    ll m = ceil(sqrt(p)), t = b;
    mp.clear();
    for (ll i = 0; i <= m; i++) {
        mp[t] = i;
        t = t * a % p;
    }
    ll A = power(a, m, p);
    t = k * A % p;
    for (ll i = 1; i <= m; i++) {
        ll ans = t;
        t = t * A % p;
        if (mp.find(ans) != mp.end()) {
            ans = i * m - mp[ans] + step;
            return 0 * printf("%lld\n", ans);
        }
    }
    puts("No Solution");
}

int main() {
    ll a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    EX_BSGS(a, b, c);
    return 0;
}