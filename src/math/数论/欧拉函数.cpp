//欧拉函数离线
void Init () {
    for (int i=0; i<maxn; i++) eular[i] = i;
    for (int i=2; i<maxn; i++)
        if (eular[i] == i) {
            eular[i] = eular[i] / i * (i - 1);
            for (int j=i+i; j<maxn; j+=i) eular[j] = eular[j] / i * (i - 1);
        }
}

//欧拉函数在线
int eular(int n) {
    int number = 1;
    for(int i=2; i*i <= n; i++)
        if(n%i == 0){
            n /= i, number *= (i-1);
            while(n%i == 0) n /= i, number *= i;
        }
    return n>1?number*(n-1):number;
}

//欧拉函数（小于n的正整数中与n互质的数的数目）