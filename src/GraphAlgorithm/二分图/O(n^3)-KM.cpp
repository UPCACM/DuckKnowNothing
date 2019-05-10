const int maxn = 307, INF = 0x3f3f3f3f;
//n和m的下标从0开始
int n, m;//n个女生（左），m个男生（右）
int love[maxn][maxn];//love[i][j]表示第i个女生对第j个男生的好感度
int ex_girl[maxn];//第i个女生的当前期望值为ex_girl[i]
int ex_boy[maxn];//同上
bool vis_girl[maxn];//标记在当前配对过程中girl[i]有没有被访问过
bool vis_boy[maxn];//同上
int match[maxn];//match[boy] = girl，说明这个boy和girl已经配对了，没有则为-1
int slack[maxn];//记录每个男生如果能被妹子倾心最少还需要多少期望值

/*
注意！！！！mp的初始值一定要给的很夸张！！！不然dfs过程中有可能tmp=0也能成立！
*/

bool dfs(int girl) {
    vis_girl[girl] = true;
    for(int boy = 0 ; boy < m ; boy++) {
        if(vis_boy[boy]) continue;//每一轮匹配，每个男生只尝试一次
        int gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];
        if(gap == 0) {//如果符合要求
            vis_boy[boy] = true;
            if(match[boy] == -1 || dfs(match[boy])) {
                //找到一个没有配对的男生 或者是 和这个男生配对的女生可以找到别人
                match[boy] = girl;
                return true;
            }
        } else {
            slack[boy] = min(slack[boy],gap);
            //可以理解为这个男生要能够得到配对的话最少还需要多少期望
        }
    }
    return false;
}

int KM() {
    clr(match, -1);//初始每个男生都没有匹配的女生
    clr(ex_boy, 0);//初始每个男生的期望值
    for(int i=0 ; i<n ; i++) {
        //每个女生的初始期望值是与她相连的男生最大好感度
        ex_girl[i] = love[i][0];
        for(int j=1 ; j<m ; j++) {
            ex_girl[i] = max(ex_girl[i], love[i][j]);
        }
    }
    for(int i=0 ; i<n ; i++) {
        //尝试为每一个女生解决归宿问题
        clr(slack, INF);//初始化为最大，随后取最小值
        while(true) {
            //为每个女生解决归宿问题的方法是：
            //如果找不到男票就降低自己的期望值，直到找到为止
            clr(vis_girl,0);
            clr(vis_boy,0);
            if(dfs(i)) break;//找到归宿，退出循环
            //如果找不到，就降低妹子的期望值
            int d = INF;//能够降低的最小期望值derta
            for(int j = 0; j<m ; j++) {
                //遍历所有一点在匈牙利树中另一点不在匈牙利树种的边
                //slack[i]的值是girl[i] 所在边的 端点权值之和-边的权值
                //取它们中的最小值，就是最小可以松弛的期望值
                if(!vis_boy[j]) d = min(d, slack[j]);
            }
            for(int j = 0; j<n ; j++) {
                //对每个访问过的女生减少期望
                if(vis_girl[j]) ex_girl[j] -= d;
            }
            for(int j = 0; j<m ; j++) {
                //所有访问过的男生增加期望
                if(vis_boy[j]) ex_boy[j] += d;
                //所有没访问过的男生距离自己被配对又更近了一步
                else slack[j] -= d;
            }
        }
    }
    //配对完成，求出所有的好感度和
    int res = 0;
    for (int i = 0; i < m ; i++)
        if(match[i] != -1) res += love[match[i]][i];
    return res;
}


//HDU-2255
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <list>
#include <iomanip>
#include <functional>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#define edl putchar('\n')
#define clr(a,b) memset(a,b,sizeof a)
using namespace std;
const int maxn = 307, INF = 0x3f3f3f3f;

int love[maxn][maxn],n;
int ex_girl[maxn];
int ex_boy[maxn];
bool vis_girl[maxn];
bool vis_boy[maxn];
int match[maxn];
int slack[maxn];

bool dfs(int girl) {
    vis_girl[girl] = true;
    for(int boy = 0 ; boy < n ; boy++) {
        if(vis_boy[boy]) continue;
        int gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];
        if(gap == 0) {
            vis_boy[boy] = true;
            if(match[boy] == -1 || dfs(match[boy])) {
                match[boy] = girl;
                return true;
            }
        } else {
            slack[boy] = min(slack[boy],gap);
        }
    }
    return false;
}

int KM() {
    clr(match, -1);
    clr(ex_boy, 0);
    for(int i=0 ; i<n ; i++) {
        ex_girl[i] = love[i][0];
        for(int j=1 ; j<n ; j++) {
            ex_girl[i] = max(ex_girl[i], love[i][j]);
        }
    }
    for(int i=0 ; i<n ; i++) {
        fill(slack, slack+n, INF);
        while(true) {
            clr(vis_girl,0);
            clr(vis_boy,0);
            if(dfs(i)) break;
            int d = INF;
            for(int j = 0; j<n ; j++)
                if(!vis_boy[j]) d = min(d, slack[j]);
            for(int j = 0; j<n ; j++) {
                if(vis_girl[j]) ex_girl[j] -= d;
                if(vis_boy[j]) ex_boy[j] += d;
                else slack[j] -= d;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n ; i++)
        res += love[match[i]][i];
    return res;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(~scanf("%d",&n)) {
        for(int i=0 ; i<n ; i++)
            for(int j=0 ; j<n ; j++)
                scanf("%d",&love[i][j]);
        printf("%d\n",KM());
    }
    return 0;
}
