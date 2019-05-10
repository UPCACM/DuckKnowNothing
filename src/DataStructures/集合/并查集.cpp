const int maxn = (int)1e5+7;
int pre[maxn],height[maxn];
//pre就不解释了，height是当前树高

int Find(int x) {//while以及附帶路徑壓縮的版本，遞歸在數據量比較大的時候可能爆
    if(x==pre[x]) return x;
    int p=x,q;
    while(x!=pre[x]) x=pre[x];
    while(p!=pre[p]) {
        q=pre[p];
        pre[p]=x;
        p=q;
    }
    return x;
}

void Add(int i, int j) {
    int x=Find(i),y=Find(j);
    if(x==y) return ;
    if(height[x]<height[y]) pre[x]=y;
    else {
        if(height[x]==height[y]) height[x]++;
        pre[y]=x;
    }
    return ;
}
