// luogu3796
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std; 
const int maxn=1000500;
const int sigsize=26;
struct AC
{
    int ch[maxn][sigsize],f[maxn],sz;
    vector<int> val[maxn];
    AC(){
        memset(ch[0],0,sizeof ch[0]);
        sz=0;
        val[0].clear();
    }
    int idx(char c){return c-'a';};
    void insert(char *s,int x){
        if(x==0){
            memset(ch[0],0,sizeof ch[0]);
            sz=0;
            val[0].clear();
        }
        int u=0;
        for (int i = 0; s[i] != '\0'; ++i)
        {
            int c=idx(s[i]);
            if(ch[u][c]) u=ch[u][c];
            else{
                ++sz;
                memset(ch[sz],0,sizeof ch[sz]);
                val[sz].clear();
                ch[u][c]=sz;
                u=sz;
            }
        }
        val[u].push_back(x);
    }
    void get_fail(){
        f[0]=0;
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for (int i = 0; i < 26; ++i)
            {
                if(!ch[u][i]) continue;
                int v=ch[u][i],pre=f[u];
                while(pre&&!ch[pre][i]) pre=f[pre];
                f[v]=ch[pre][i];
                if(!u) f[v]=0;
                q.push(v);
            }
        }
    }
    void query(char *s,int cnt[]){
        int u=0;
        for (int i = 0; s[i] != '\0'; ++i)
        {
            int c=idx(s[i]);
            while(u&&!ch[u][c]) u=f[u];
            if(ch[u][c]) u=ch[u][c];
            int v=u;
            while(v){
                for (int i = 0; i < val[v].size(); ++i)
                {
                    cnt[val[v][i]]++;
                }
                v=f[v];
            }
        }
    }
}ac;
char T[1000050];
int main(int argc, char const *argv[])
{
    int n;
    while(~scanf("%d", &n)&&n){
        char s[n+1][80];
        for (int i = 0; i < n; ++i)
        {
            scanf("%s",s[i]);
            ac.insert(s[i],i);
        }
        ac.get_fail();
        scanf("%s",T);
        int cnt[n];
        memset(cnt,0,sizeof cnt);
        ac.query(T,cnt);
        int M=0;
        for (int i = 0; i < n; ++i)
        {
            M=max(M,cnt[i]);
        }
        printf("%d\n", M);
        for (int i = 0; i < n; ++i)
        {
            if(cnt[i]==M)
                printf("%s\n", s[i]);
        }
    }
    return 0;
}