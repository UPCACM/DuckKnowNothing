#define maxn 1007
#define maxn 100005
struct node
{
    int x;
};
vector<node> V[maxn]; //储存树的结构，也可以使用邻接表
int E[maxn * 2], D[maxn * 2], first[maxn]; //标号数列   深度数列   某个标号第一次出现的位置
int vis[maxn], dis[maxn], n, m, top = 1, root[maxn], st; //dis[] 若边有权值可求距离   root[] 求整棵树的根
int dp[30][maxn * 2];  //储存某区间最小值的下标

//DFS树得到欧拉序列
void dfs(int u, int dep) {
    vis[u] = 1, E[top] = u, D[top] = dep, first[u] = top++;
    for (int i = 0; i < V[u].size(); i++)
        if (!vis[V[u][i].x]) {//储存时双向，因此判断是否为父节点
            int v = V[u][i].x;
            dfs(v, dep + 1);
            E[top] = u, D[top++] = dep; //dfs回溯过程必须储存，否则原理就错误了
        }
}

//ST预处理
void ST(int num) {
    for (int i = 1; i <= num; i++) dp[0][i] = i;//初始状态
    for (int i = 1; i <= log2(num); i++) //控制区间长度
        for (int j = 1; j <= num; j++) //控制区间左端点
            if (j + (1 << i) - 1 <= num) {
                int a = dp[i - 1][j], b = dp[i - 1][j + (1 << i >> 1)];
                if (D[a] < D[b]) dp[i][j] = a;//储存D数组下标，以便找到对应的E数组
                else dp[i][j] = b;
            }
}

//RMQ查询
int RMQ(int x, int y) {
    int k = (int) log2(y - x + 1.0);
    int a = dp[k][x], b = dp[k][y - (1 << k) + 1];
    if (D[a] < D[b]) return a;//前后两段比较
    return b;
}
