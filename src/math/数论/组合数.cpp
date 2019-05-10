/*
在线算法
*/

// O(n)在线求组合数

const int maxn = int(2e5) + 7, mod = int(1e9) + 7;
namespace combination {
    typedef long long ll;
    ll fac[maxn], inv[maxn];
    bool flag = false;
    ll pow(ll p, ll q) {
        ll ret = 1;
        while (q) {
            if (q & 1) ret = ret * p % mod;
            p = p * p % mod;
            q >>= 1;
        }
        return ret;
    }
    void init(int upper) {
        fac[0] = 1;
        for (int i = 1; i <= upper; i++) fac[i] = fac[i - 1] * i % mod;
        inv[upper] = pow(fac[upper], mod - 2);
        for (int i = upper - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    }
    ll C(ll n, ll m) {
        if (!flag) init(maxn - 7), flag = true;
        if (n == m || m == 0) return 1ll;
        return fac[n] * inv[m] % mod * inv[n - m] % mod;
    }
}
using combination::C;

// Lucas

ll mod;
ll power_mod(ll p, ll q) {
    ll ans = 1;
    p %= mod;
    while (q) {
        if (q & 1) ans = ans * p % mod;
        q >>= 1, p = p * p % mod;
    }
    return ans;
}

ll C(ll n, ll m) {
    if (m > n) return 0;
    ll ans = 1;
    for (int i = 1; i <= m; i++) {
        ll a = (n + i - m) % mod;
        ll b = i % mod;
        ans = ans * (a * power_mod(b, mod - 2) % mod) % mod;
    }
    return ans;
}

ll Lucas(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    return C(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod;
}

/*
扩展Lucas
*/

long long POW(long long a,long long b,long long mod) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long POW(long long a,long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}


long long exGcd(long long a,long long b,long long &x,long long &y) {
    long long t, d;
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    d = exGcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

bool modular(long long a[],long long m[],long long k) {
    long long d, t, c, x, y, i;
    for (i = 2; i <= k; i++) {
        d = exGcd(m[1], m[i], x, y);
        c = a[i] - a[1];
        if (c % d) return false;
        t = m[i] / d;
        x = (c / d * x % t + t) % t;
        a[1] = m[1] * x + a[1];
        m[1] = m[1] * m[i] / d;
    }
    return true;
}



long long reverse(long long a,long long b) {
    long long x, y;
    exGcd(a, b, x, y);
    return (x % b + b) % b;
}

long long C(long long n,long long m,long long mod) {
    if (m > n) return 0;
    long long ans = 1, i, a, b;
    for (i = 1; i <= m; i++) {
        a = (n + 1 - i) % mod;
        b = reverse(i % mod, mod);
        ans = ans * a % mod * b % mod;
    }
    return ans;
}

long long C1(long long n,long long m,long long mod) {
    if (m == 0) return 1;
    return C(n % mod, m % mod, mod) * C1(n / mod, m / mod, mod) % mod;
}

long long cal(long long n,long long p,long long t) {
    if (!n) return 1;
    long long x = POW(p, t), i, y = n / x, temp = 1;
    for (i = 1; i <= x; i++) if (i % p) temp = temp * i % x;
    long long ans = POW(temp, y, x);
    for (i = y * x + 1; i <= n; i++) if (i % p) ans = ans * i % x;
    return ans * cal(n / p, p, t) % x;
}

long long C2(long long n,long long m,long long p,long long t) {
    long long x = POW(p, t);
    long long a, b, c, ap = 0, bp = 0, cp = 0, temp;
    for (temp = n; temp; temp /= p) ap += temp / p;
    for (temp = m; temp; temp /= p) bp += temp / p;
    for (temp = n - m; temp; temp /= p) cp += temp / p;
    ap = ap - bp - cp;
    long long ans = POW(p, ap, x);
    a = cal(n, p, t);
    b = cal(m, p, t);
    c = cal(n - m, p, t);
    ans = ans * a % x * reverse(b, x) % x * reverse(c, x) % x;
    return ans;
}

//计算C(n,m)%mod
long long Lucas(long long n,long long m,long long mod) {
    long long i, t, cnt = 0;
    long long A[205], M[205];
    for (i = 2; i * i <= mod; i++)
        if (mod % i == 0) {
            t = 0;
            while (mod % i == 0) {
                t++;
                mod /= i;
            }
            M[++cnt] = POW(i, t);
            if (t == 1) A[cnt] = C1(n, m, i);
            else A[cnt] = C2(n, m, i, t);
        }
    if (mod > 1) {
        M[++cnt] = mod;
        A[cnt] = C1(n, m, mod);
    }
    modular(A, M, cnt);
    return A[1];
}

/*
离线打表
*/

long long C[maxn][maxn];

void get_C() {
    C[0][0] = 1;
    for(int i = 1;i <= maxn; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}
