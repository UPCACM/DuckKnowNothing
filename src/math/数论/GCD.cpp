ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    if (!(a & 1) && !(b & 1)) return 2 * gcd(a >> 1, b >> 1);
    if (!(a & 1)) return gcd(a >> 1, b);
    if (!(b & 1)) return gcd(a, b >> 1);
    return gcd((a + b) >> 1, (a - b) >> 1);
}

ll gcd(ll p, ll q) { return q ? gcd(q, p % q) : p; }

inline ll gcd(ll p, ll q, ll tmp = 0) {
    while (q) tmp = p % q, p = q, q = tmp;
    return p;
}

ll gcd(ll a, ll b) {
    while (b ^= a ^= b ^= a %= b);
    return a;
}