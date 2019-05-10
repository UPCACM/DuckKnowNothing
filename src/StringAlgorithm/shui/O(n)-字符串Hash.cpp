//多项式哈希
typedef unsigned long long ull;
const int N = 100000 + 5;
const ull base = 163;
char s[N];
ull hash[N];
 
void init() {//处理hash值, 字符串下标从1开始
	p[0] = 1;
	hash[0] = 0;
	int n = strlen(s + 1);
	for(int i = 1; i <=100000; i ++) p[i] = p[i-1] * base;
	for(int i = 1; i <= n; i ++) hash[i] = hash[i - 1] * base + (s[i] - 'a' + 1);
}
 
ull get(int l, int r, ull g[]) {//取出g里l - r里面的字符串的hash值
    return g[r] - g[l - 1] * p[r - l + 1];
}


/**********/

unsigned int BKDRHash(char *str){
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str)
        hash = hash * seed + (*str++);
    return (hash & 0x7FFFFFFF);
}

void ha(char *p, int len, unsigned ll h[]) {
    h[len] = 0;
    for (int i = len - 1; i >= 0; i--) {
        h[i] = h[i + 1] * 1008611 + p[i];
    }
}