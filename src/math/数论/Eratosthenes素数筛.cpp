#include <bits/stdc++.h>
const int maxn = 1007;
int minimal_prime_factor[maxn], prime[maxn];
int primes(int upper) {
    // i的最小质因子为minimal_prime_factor[i]
    memset(minimal_prime_factor, 0, sizeof(minimal_prime_factor));
    int cnt_prime = 0; // 质数数量
    for (int i = 2; i <= upper; i++) {
        if (minimal_prime_factor[i] == 0) { // i是质数
            minimal_prime_factor[i] = i;
            prime[++cnt_prime] = i;
        }
        // 给当前的数i乘上一个质因子
        int tmp = upper / i;
        for (int j = 1; j <= cnt_prime; j++) {
            // i有比prime[j]更小的因子，或者超出upper的范围
            if (prime[j] > minimal_prime_factor[i] || prime[j] > tmp) break;
            // prime[j]是合数i * prime[j]的最小质因子
            minimal_prime_factor[i * prime[j]] = prime[j];
        }
    }
}
int main() {
    int cnt_prime = primes(1000);
    for (int i = 1; i <= cnt_prime; i++) printf("%d ", prime[i]);
    return 0;
}