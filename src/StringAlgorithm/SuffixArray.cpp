#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100050;
char str[maxn];
namespace suffixArray {
    int sa[maxn],x[maxn],c[maxn],t[maxn],n;
    int height[maxn],*rank=x;
    char *str;
    bool cmp(int u,int v,int l) {
        return x[u]==x[v]&&x[u+l]==x[v+l];
    }
    void calHeight();
    void da(char *_str,int _n) {
        int m=255;
        str=_str,n=_n;x[n+1]=x[0]=0,str[n+1]=str[0]=0,t[n+1]=0;// !!注意计算中t与x数组交换多次，所以也要设定n+1处值
        for(int i = 0; i <= m; ++i) c[i]=0;
        for(int i = 1; i <= n; ++i) c[x[i]=str[i]]++;
        for(int i = 1; i <= m; ++i) c[i]+=c[i-1];
        for(int i = n; i >= 1; --i) sa[c[x[i]]--]=i;

        for(int l = 1; l <= n; l<<=1) {
            int cnt=0;
            for(int i = n-l+1; i <= n; ++i) t[++cnt]=i;
            for(int i = 1; i <= n; ++i) {
                if(sa[i]>l) t[++cnt]=sa[i]-l;
            }

            for(int i = 0; i <= m; ++i) c[i]=0;
            for(int i = 1; i <= n; ++i) c[x[i]]++;
            for(int i = 1; i <= m; ++i) c[i]+=c[i-1];
            for(int i = n; i >= 1; --i) sa[c[x[t[i]]]--]=t[i];

            m=0,t[sa[1]]=++m;
            for(int i = 2; i <= n; ++i) {
                if(cmp(sa[i],sa[i-1],l)) t[sa[i]]=m;
                else t[sa[i]]=++m;
            }
            swap(x,t);
            if(m==n) break;
        }
        calHeight();
    }
    void calHeight() {
        int h=1;
        for(int i = 1; i <= n; ++i) {
            --h;
            if(h<0) h=0;
            while(str[i+h]==str[sa[rank[i]-1]+h]) ++h;
            height[rank[i]]=h;
        }
    }
    void debug(int *arr=sa) {
        for(int i = 1; i <= n; ++i) {
            printf("%d%s", arr[i],i==n?"\n":" ");
        }
    }
}
int main() {
    scanf("%s", str+1);
    int n=strlen(str+1);
    suffixArray::da(str,n);
    using suffixArray::sa;
    using suffixArray::height;
    for(int i = 1; i <= n; ++i) {
        printf("%d%s", sa[i],i==n?"\n":" ");
    }
    for(int i = 2; i <= n; ++i) {
        printf("%d%s", height[i],i==n?"\n":" ");
    }
    return 0;
}
