#include <bits/stdc++.h>
const int MAXN=5e4+10;
#define ll long long
const ll INF=1e5;
using namespace std;
int root,pos,k,n;
typedef struct node{
    int p[6],c[2];ll maxx[6],minn[6];
    friend bool operator <(node aa,node bb){
        if(aa.p[pos]!=bb.p[pos])return aa.p[pos]<bb.p[pos];
		for(int i = 1;i<=k;i++) if(aa.p[i]!=bb.p[i]) return aa.p[i]<bb.p[i];
    }
}node;
node a[MAXN<<2];
void up(int x,int y){
    for(int i=1;i<=k;i++)a[x].maxx[i]=max(a[x].maxx[i],a[y].maxx[i]),a[x].minn[i]=min(a[x].minn[i],a[y].minn[i]);
}
int build(int l,int r,int now){
    if(l>r)return 0;
    int mid=(l+r)>>1;
    pos=now,nth_element(a+l,a+mid,a+r+1);
    for(int i=1;i<=k;i++)a[mid].maxx[i]=a[mid].minn[i]=a[mid].p[i];
    a[mid].c[0]=a[mid].c[1]=0;
    if(l<mid)a[mid].c[0]=build(l,mid-1,now%k+1),up(mid,a[mid].c[0]);
    if(r>mid)a[mid].c[1]=build(mid+1,r,now%k+1),up(mid,a[mid].c[1]);
    return mid;
}
typedef struct Tmp{
    int p[6];ll dis;
    friend bool operator<(Tmp aa,Tmp bb){return aa.dis<bb.dis;}
}Tmp;
ll dist(node aa,node bb){
    ll ans=0;
    for(int i=1;i<=k;i++)ans+=1LL*(aa.p[i]-bb.p[i])*(aa.p[i]-bb.p[i]);
    return ans;
}
priority_queue<Tmp>que;
node t;
stack<Tmp>s;
ll get_ans(node aa,node bb){
    ll ans=0;
    for(int i=1;i<=k;i++){
        ans+=min(1LL*(aa.minn[i]-bb.p[i])*(aa.minn[i]-bb.p[i]),1LL*(bb.p[i]-aa.maxx[i])*(bb.p[i]-aa.maxx[i]));
    }
    return ans;
}
void query(int x,int now){
	if(!x)return ;
	ll res=dist(a[x],t);
	if(res<(que.top()).dis){
		que.pop();
		Tmp tt;tt.dis=res;
		for(int i=1;i<=k;i++)tt.p[i]=a[x].p[i];
		que.push(tt);
	}
	 ll tt=t.p[now]-a[x].p[now];
	 if(tt<=0){
		query(a[x].c[0],now%k+1);
		 if(que.top().dis>tt*tt)
			 query(a[x].c[1],now%k+1);
	 }
	 else{
		query(a[x].c[1],now%k+1);
		 if(que.top().dis>tt*tt)
			 query(a[x].c[0],now%k+1);        
	 }
}
int main(){
    while(scanf("%d%d",&n,&k)!=EOF){
		for(int i = 1;i<=k;i++) a[0].minn[i] = INF,a[0].maxx[i] = -INF;
		for(int i = 1;i<=n;i++) for(int j = 1;j<=k;j++) scanf("%d",&a[i].p[j]);
        root=build(1,n,1);
		int q;
		scanf("%d",&q);
        while(q--){
			for(int i = 1;i<=k;i++) scanf("%d",&t.p[i]);
			int K;
			scanf("%d",&K);
            Tmp t1;t1.dis=1e15;
			for(int i = 1;i<=K;i++) que.push(t1);
            query(root,1);
            while(!que.empty())s.push(que.top()),que.pop();
            printf("the closest %d points are:\n",K);
            while(!s.empty()){
                Tmp tt=s.top();
                for(int i=1;i<=k;i++){
                    if(i!=k)printf("%d ",tt.p[i]);
                    else printf("%d\n",tt.p[i]);
                }
                s.pop();
            }
        }
    }
    return 0;
}
