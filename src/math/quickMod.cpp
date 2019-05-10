// 高端版，速度很快
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef __uint128_t u128;
int T, k;
ull A0, A1, M0, M1, C, M;
namespace Modll { // 加减乘请务必严格按照模版中的写法来写，不要有任何魔改
    static ull mod, inv, r2;
    struct mll { // 开始进行运算之前务必调用一下set_mod函数
        ull val;
        mll(ull tmp = 0) : val(reduce(u128(tmp) * r2)) {}
        static void set_mod(ull m) {
            mod = m;
            assert(mod & 1);
            inv = m;
            for (int i = 0; i < 5; i++) inv *= 2 - inv * m;
            r2 = -u128(m) % m;
        }
        static ull reduce(u128 x) {
            ull y = ull(x >> 64) - ull((u128(ull(x) * inv) * mod) >> 64);
            return ll(y) < 0 ? y + mod : y;
        }
        mll &operator += (mll tmp) {
            val += tmp.val - mod;
            if (ll(val) < 0) val += mod;
            return *this;
        }
        mll operator + (mll tmp) const { return mll(*this) += tmp; }
        mll &operator -= (mll tmp) {
            val -= tmp.val;
            if (ll(val) < 0) val += mod;
            return *this;
        }
        mll operator - (mll tmp) const { return mll(*this) -= tmp; }
        mll &operator *= (mll tmp) {
            val = reduce(u128(val) * tmp.val);
            return *this;
        }
        mll operator * (mll tmp) const { return mll(*this) *= tmp; }
        ull value() const { return reduce(val); }
    };
} using Modll::mll;
int main() {
#ifdef LOCAL
    freopen("../in", "r", stdin);
#endif
    for (scanf("%d", &T); T; T--) {
        std::cin >> A0 >> A1 >> M0 >> M1 >> C >> M >> k;
        mll::set_mod(M);
        mll a0 = A0, a1 = A1, m0 = M0, m1 = M1, c = C, ans = a0 * a1, tmp;
        for (int i = 2; i <= k; i++) {
            tmp = m0 * a1 + m1 * a0 + c;
            ans *= tmp;
            a0 = a1, a1 = tmp;
        }
        printf("%llu\n", ans.value());
    }
}