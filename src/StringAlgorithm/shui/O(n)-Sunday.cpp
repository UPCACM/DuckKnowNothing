const int maxn = 1007;
int jump[maxn];

void Sunday(char *s, char *p) {
    int lens = int(strlen(s)), lenp = int(strlen(p));
    for (int i = 0; i < lenp; i++) jump[p[i]] = i;
    int i = 0, j, k;
    while (j = i, k = 0, i <= lens - lenp) {
        while (j < lens && k < lenp && s[j] == p[k]) j++, k++;
        if (k == lenp) printf("Find \"p\" in \"s\" at %d\n", i);
        if (i + lenp < lens) i += (lenp - jump[s[i + lenp]]);
        else return ;
    }
    printf("Not found\n");
}