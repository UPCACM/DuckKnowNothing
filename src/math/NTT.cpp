#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100050;
const int MOD=998244353;
struct NTT
{
    ll Pow(ll x,ll n) {
        ll ans=1,base=x%MOD;
        while(n) {
            if(n&1) ans=ans*base%MOD;
            base=base*base%MOD;
            n>>=1;
        }
        return ans;
    }
    ll getInv(ll x) {
        return x==1?1:getInv(MOD%x)*(MOD-MOD/x)%MOD;
    }
    int t[maxn*2];
	int _n,idx[maxn*4];
	void rev(vector<int>&a,int n) {
		if(_n!=n) {
			_n=n;
			for(int i = 0; i < n; ++i) {
				idx[i]=(idx[i>>1]>>1)+(i&1)*(n>>1);
			}
		}
		for(int i = 0; i < n; ++i) {
			if(i<idx[i]) swap(a[i],a[idx[i]]);
		}
	}

	// 计算数组a的点值表达并存在数组a中
    void ntt(vector<int>&a,int n,int op) { 
		rev(a,n);
        for(int i = 1; i < n; i<<=1) {
            ll gn,g=1;
            if(op==1) gn=Pow(3,(MOD-1)/i/2);
            else gn=Pow(3,(MOD-1)/i/2*(i*2-1));
            for(int j = 0; j < n; j+=(i<<1)) {
                g=1;
                for(int k = j; k < j+i; ++k) {
                    ll u=a[k],v=a[k+i];
                    a[k]=(u+g*v)%MOD;
                    a[k+i]=(u-g*v)%MOD;
                    g=g*gn%MOD;
                }
            }
        }
        if(op==-1) {
            ll t=getInv(n);
            for(int i = 0; i < n; ++i) {
                a[i]=(ll)a[i]*t%MOD;
            }
        }
    }

	// a，b分别是两个多项式的系数数组，计算两个多项式乘积并存到a中
    void mul(vector<int>&a,vector<int>&b) {
        int n=1;
        while(n<a.size()+b.size()-1) n<<=1;
        a.resize(n),b.resize(n);
        ntt(a,n,1);
        ntt(b,n,1);
        for(int i = 0; i < n; ++i) a[i]=(ll)a[i]*b[i]%MOD;
        ntt(a,n,-1);
        while(a.size()>1&&a.back()==0) a.pop_back();
    }
}ntt;
