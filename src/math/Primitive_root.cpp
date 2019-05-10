// 调用getG返回n的第一个原根
// ! 不支持非素数
namespace Primitive_root {
	int phi(int n) {
		int ans=n;
		for(int i = 2; i*i <= n; ++i) {
			if(n%i==0) {
				ans=ans/i*(i-1);
				while(n%i==0) n/=i;
			}
		}
		if(n>1) ans=ans/n*(n-1);
		return ans;
	}
	ll Pow(ll x, ll n, ll mod) {
		ll ans=1,base=x%mod;
		while(n) {
			if(n&1) ans=ans*base%mod;
			base=base*base%mod;
			n>>=1;
		}
		return ans;
	}
	vector<int> fac;
	bool test(int g,int eu,int mod) {
		for(auto e:fac) {
			if(Pow(g,eu/e,mod)==1) return false;
		}
		return true;
	}
	int getG(int n) {
		int eu=phi(n),eu0=eu;
		fac.clear();
		for(int i = 2; i*i <= n; ++i) {
			if(eu%i==0) {
				fac.push_back(i);
				while(eu%i==0) eu/=i;
			}
		}
		if(eu>1) fac.push_back(eu);
		eu=eu0;
		int g=2;
		while(!test(g,eu,n)) ++g;
		return g;
	}
}
