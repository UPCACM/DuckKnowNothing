#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
const int maxn=1000050;
ll getInv(ll x) {
	return x==1?x:getInv(MOD%x)*(MOD-MOD/x)%MOD;
}
ll Pow(ll x,ll n) {
	ll ans=1,base=x%MOD;
	while(n) {
		if(n&1) ans=ans*base%MOD;
		base=base*base%MOD;
		n>>=1;
	}
	return ans;
}
vector<int> idx;
void rev(vector<int> &a,int n) {
	if(idx.size()!=n) {
		idx.assign(n,0);
		for(int i = 0; i < n; ++i) {
			idx[i]=(idx[i>>1]>>1)+(i&1)*(n>>1);
		}
	}
	for(int i = 0; i < n; ++i) {
		if(i<idx[i]) swap(a[i],a[idx[i]]);
	}
}
void ntt(vector<int>& a,int n,int op) {
	rev(a,n);
	for(int l = 2; l <= n; l<<=1) {
		ll wn=Pow(3,(MOD-1)/l);
		if(op==-1) wn=getInv(wn);
		for(int i = 0; i < n; i+=l) {
			ll w=1;
			for(int j = i; j < i+(l>>1); ++j) {
				ll u=a[j],v=a[j+(l>>1)];
				a[j]=(u+v*w)%MOD;
				a[j+(l>>1)]=(u-v*w)%MOD;
				w=w*wn%MOD;
			}
		}
	}
	if(op==-1) {
		ll t=getInv(n);
		for(int i = 0; i < n; ++i) a[i]=(ll)a[i]*t%MOD;
	}
}
void deb(vector<int>&a) {
	for(auto &e:a) cout<<(e+MOD)%MOD<<" ";
	cout<<endl;
}
int inv[maxn*2];
vector<int> polydiff(vector<int>&a,int n) {
	vector<int> ans(n);
	for(int i = 0; i < n-1; ++i) {
		ans[i]=(ll)(i+1)*a[i+1]%MOD;
	}
	return ans;
}
vector<int> polyInv(vector<int> &a,int n) {
	vector<int> ans(1,getInv(a[0]));
	for(int l = 2; l <= n; l<<=1) {
		vector<int> b(a.begin(),a.begin()+l);
		ans.resize(l*2),b.resize(l*2);
		ntt(ans,l*2,1),ntt(b,l*2,1);
		for(int i = 0; i < l*2; ++i) ans[i]=(ll)(2ll-(ll)b[i]*ans[i]%MOD)*ans[i]%MOD;
		ntt(ans,l*2,-1);
		for(int i = l; i < l*2; ++i) ans[i]=0;
	}
	ans.resize(n);
	return ans;
}
vector<int> polyln(vector<int>& a,int n) {
	vector<int> da=polydiff(a,n),inva=polyInv(a,n);
	da.resize(n*2),inva.resize(n*2);
	ntt(da,n*2,1),ntt(inva,n*2,1);
	for(int i = 0; i < n*2; ++i) da[i]=(ll)da[i]*inva[i]%MOD;
	ntt(da,n*2,-1);
	vector<int> ans(n);
	for(int i = 1; i < n; ++i) ans[i]=(ll)da[i-1]*inv[i]%MOD;
	return ans;
}
vector<int> polyExp(vector<int>& a,int n) {
	vector<int> ans(1,1);
	ans.resize(2);
	for(int l = 2; l <= n; l<<=1) {
		vector<int> lnf0=polyln(ans,l),b(a.begin(),a.begin()+l);
		ans.resize(l*2),lnf0.resize(l*2),b.resize(l*2);
		ntt(ans,l*2,1),ntt(lnf0,l*2,1),ntt(b,l*2,1);
		for(int i = 0; i < l*2; ++i) ans[i]=(ll)ans[i]*(1ll-(ll)lnf0[i]+b[i])%MOD;
		ntt(ans,l*2,-1);
		for(int i = l; i < l*2; ++i) ans[i]=0;
	}
	ans.resize(n);
	return ans;
}
void init() {
	inv[1]=1;
	for(int i = 2; i < maxn*2; ++i) inv[i]=(ll)inv[MOD%i]*(MOD-MOD/i)%MOD;
}
int a[maxn];
vector<int> get(int l,int r) {
	if(l==r) return vector<int>{1,a[l]};
	int mid=(l+r)>>1;
	vector<int> a=get(l,mid),b=get(mid+1,r);
	int n=1;
	while(n<=(int)a.size()+(int)b.size()-2) n<<=1;
	a.resize(n),b.resize(n);
	ntt(a,n,1),ntt(b,n,1);
	for(int i = 0; i < n; ++i) a[i]=(ll)a[i]*b[i]%MOD;
	ntt(a,n,-1);
	while(a.size()>1&&a.back()==0) a.pop_back();
	return a;
}
int main() {
	init();
	int n,m;
	scanf("%d%d", &n,&m);
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	int N=1;
	while(N<=m) N<<=1;
	vector<int> g(N);
	for(int i = 0; i < N; ++i) {
		if(i==0) g[i]=1;
		else g[i]=(ll)g[i-1]*inv[i+1]%MOD;
	}
	g=polyln(g,N);
	vector<int> f=get(1,n);
	f.resize(N);
	f=polyln(f,N);
	for(int i = 1; i < N; ++i) {
		ll t=-(ll)f[i]*i%MOD;
		if(i&1) t=-t;
		g[i]=(ll)g[i]*t%MOD;
	}
	g=polyExp(g,N);
	ll ans=g[m];
	for(int i = 1; i <= m; ++i) ans=ans*i%MOD;
	ans=(ans+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}
