// 查询直角梯形内的点数量
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100050;
int n;
struct Query {
	int type,x,y,x2,d;
	void read() {
		scanf("%d%d%d", &type,&x,&y);
		if(type==2) scanf("%d%d", &x2,&d);
	}
};
struct CDQ {
	struct node {
		int idx,val;
		ll x,y;
		bool operator <(const node&t)const {
			return x<t.x;
		}
		void print() {
			cout<<idx<<" "<<val<<" "<<x<<" "<<y<<endl;
		}
	}a[maxn],tmp[maxn];
	ll t[maxn];
	void discrete() {
		for(int i = 0; i < n; ++i) t[i]=a[i].y;
		sort(t,t+n);
		for(int i = 0; i < n; ++i) a[i].y=lower_bound(t,t+n,a[i].y)-t+1;
	}
	int f1,f2;// [f1==1]代表第一键值要严格小于，[f2==1]代表第二关键字严格小于
	void run(int _f1,int _f2) {
		f1=_f1,f2=_f2;
		memset(ans,0,sizeof ans);
		memset(sum,0,sizeof sum);
		discrete();
		solve(0,n-1);
	}
	int ans[maxn];
	void solve(int l,int r) {
		if(l==r) return;
		int mid=(l+r)>>1;
		solve(l,mid),solve(mid+1,r);
		int ptr=l;
		for(int i = mid+1; i <= r; ++i) {
			while(ptr<=mid && a[ptr].x<=a[i].x-f1) {
				add(a[ptr].y,a[ptr].val);
				++ptr;
			}
			if(a[i].val==0) ans[a[i].idx]+=query(a[i].y-f2);
		}
		for(int i = l; i < ptr; ++i) add(a[i].y,-a[i].val);
		merge(a+l,a+mid+1,a+mid+1,a+r+1,tmp);
		for(int i = l; i <= r; ++i) a[i]=tmp[i-l];
	}
	int sum[maxn];
	void add(int x,int val) {
		while(x<=n) sum[x]+=val,x+=(x&-x);
	}
	int query(int x) {
		int ans=0;
		while(x) ans+=sum[x],x-=(x&-x);
		return ans;
	}
}cdq;
int ans[maxn];
int main() {
	scanf("%d", &n);
	vector<Query> ques(n);
	for(int i = 0; i < n; ++i) ques[i].read();

	for(int i = 0; i < n; ++i) {
		int x=ques[i].x,y=ques[i].y,d=ques[i].d,x2=ques[i].x2,type=ques[i].type;
		if(type&1) cdq.a[i]={i,1,(ll)y,(ll)y+x};
		else cdq.a[i]={i,0,(ll)y+d,(ll)x2+y+d};
	}
	cdq.run(0,0);
	for(int i = 0; i < n; ++i) ans[i]+=cdq.ans[i];

	for(int i = 0; i < n; ++i) {
		int x=ques[i].x,y=ques[i].y,d=ques[i].d,x2=ques[i].x2,type=ques[i].type;
		if(type&1) cdq.a[i]={i,1,(ll)y,(ll)y+x};
		else cdq.a[i]={i,0,(ll)y,(ll)x2+y+d};
	}
	cdq.run(1,0);
	for(int i = 0; i < n; ++i) ans[i]-=cdq.ans[i];

	for(int i = 0; i < n; ++i) {
		int x=ques[i].x,y=ques[i].y,d=ques[i].d,x2=ques[i].x2,type=ques[i].type;
		if(type&1) cdq.a[i]={i,1,(ll)x,(ll)y};
		else cdq.a[i]={i,0,(ll)x,(ll)y+d};
	}
	cdq.run(1,0);
	for(int i = 0; i < n; ++i) ans[i]-=cdq.ans[i];

	for(int i = 0; i < n; ++i) {
		int x=ques[i].x,y=ques[i].y,d=ques[i].d,x2=ques[i].x2,type=ques[i].type;
		if(type&1) cdq.a[i]={i,1,(ll)x,(ll)y};
		else cdq.a[i]={i,0,(ll)x,(ll)y};
	}
	cdq.run(1,1);
	for(int i = 0; i < n; ++i) ans[i]+=cdq.ans[i];

	for(int i = 0; i < n; ++i) if(ques[i].type==2) printf("%d\n", ans[i]);
	return 0;
}
