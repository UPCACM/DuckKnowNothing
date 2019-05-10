int top;//这个是用作栈顶的指针
int Stack[maxn];//维护的一个栈
bool instack[maxn];//instack[i]为真表示i在栈中
int DFN[maxn],LOW[maxn];
int Belong[maxn];//Belong[i] = a; 表示i这个点属于第a个连通分量
int Bcnt,Dindex;//Bcnt用来记录连通分量的个数，Dindex表示到达某个点的时间
void tarjan(int u) {
    int v;
    DFN[u]=LOW[u] = ++ Dindex;//这里要注意 Dindex是初始化为0，这里就不能 Dindex++; 不然第一个点的DFN和LOW就为0
    Stack[++ top] = u;
    instack[u] = true;
    for (edge *e = V[u] ; e ; e = e->next) {//对所有可达边的搜索
        v = e->t;
        if (!DFN[v]) {//这个if 就是用来更新LOW[u]
            tarjan(v);
            if (LOW[v] < LOW[u]) LOW[u] = LOW[v];
        }
        else if (instack[v] && DFN[v] < LOW[u]) LOW[u] = DFN[v];
    }
    if (DFN[u] == LOW[u]) {//这里表示找完一个强连通啦
        Bcnt ++;//强连通个数加1
        do {
            v = Stack[top --];
            instack[v] = false;
            Belong[v] = Bcnt;
        }
        while (u != v);//一直到v=u都是属于第Bcnt个强连通分量
    }
}
void solve() {
    top = Bcnt = Dindex = 0;
    memset(DFN,0,sizeof(DFN));
    for (int i = 1; i <= N ; i ++) if (!DFN[i]) tarjan(i);  //这里是一定要对所有点tarjan才能求出所有的点的强连通分量
}
