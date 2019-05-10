#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
const int maxn=100050;
const double Pi=acos(-1);
struct FFT {
	struct C {
		double x,y;
		C operator +(const C&t) const {
			return (C){x+t.x,y+t.y};
		}
		C operator -(const C&t) const {
			return (C){x-t.x,y-t.y};
		}
		C operator *(const C&t) const {
			return (C){x*t.x-y*t.y,x*t.y+y*t.x};
		}
	}A[maxn*4],B[maxn*4];
	void run(int *a,int n,int *b,int m) {
		int N=1;
		while(N<n+m-1) N<<=1;
		for(int i = 0; i < n; ++i) A[i].x=a[i];
		for(int i = 0; i < m; ++i) B[i].x=b[i];
		fft(A,N,1);
		fft(B,N,1);
		for(int i = 0; i < N; ++i) A[i]=A[i]*B[i];
		fft(A,N,-1);
		for(int i = 0; i < n+m; ++i) {
			a[i]=A[i].x+0.5;
		}
	}
	int idx[maxn*4];
	void rev(C *a,int n) {
		static int _n=-1;
		if(_n!=n) {
			_n=n;
			int L=31-__builtin_clz(n);
		    for(int i = 0; i < n; ++i)
				idx[i]=(idx[i>>1]>>1)|((i&1)<<(L-1)); 
		}
		for(int i = 0; i < n; ++i) {
			if(idx[i]>i) swap(a[i],a[idx[i]]);
		}
	}
	void fft(C *a,int n,int op) {
		rev(a,n);
		for(int l = 2; l <= n; l<<=1) {
			C wn={cos(Pi*2/l*op),sin(Pi*2/l*op)};
			for(int i = 0; i < n; i+=l) {
				C w={1,0};
				for(int j = i; j < i+(l>>1); ++j) {
					C u=a[j],v=a[j+(l>>1)];
					a[j]=u+v*w;
					a[j+(l>>1)]=u-v*w;
					w=w*wn;
				}
			}
		}
		if(op==-1) {
			for(int i = 0; i < n; ++i) a[i].x/=n,a[i].y/=n;
		}
	}
}fft;
int a[maxn*2],b[maxn];
int main() {
	int n,m;
	scanf("%d%d", &n,&m);
	for(int i = 0; i <= n; ++i) scanf("%d", a+i);
	for(int i = 0; i <= m; ++i) scanf("%d", b+i);
	fft.run(a,n+1,b,m+1);
	for(int i = 0; i <= n+m; ++i) printf("%d%s", a[i],i==n+m?"\n":" ");
	return 0;
}
