// 求无向图1-n路径异或和的期望
// DP+高斯消元，time complexity O(30*n^3)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=120;
struct Edge {
	int v,w;
};
vector<Edge> G[maxn];
double a[maxn][maxn],ans[maxn];
int n,m;
const double eps=1e-9;
void solve(int d) {
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n+1; ++j) a[i][j]=0;
		a[i][i]=-1;
		if(i<n)
			for(auto e:G[i]) {
				if(e.w&(1<<d)) {
					a[i][e.v]-=1.0/G[i].size();
					a[i][n+1]+=1.0/G[i].size();
				}
				else {
					a[i][e.v]+=1.0/G[i].size();
				}
			}
	}
	for(int x = 1,y = 1; x <= n&&y <= n+1; ) {
		for(int i = x+1; i <= n; ++i) {
			if(fabs(a[i][y])>fabs(a[x][y])) swap(a[i],a[x]);
		}
		if(fabs(a[x][y])<eps) {
			++y;
			continue;
		}
		for(int i = x+1; i <= n; ++i) {
			double p=1.0/a[x][y]*a[i][y];
			for(int j = y; j <= n+1; ++j) {
				a[i][j]-=a[x][j]*p;
			}
		}
		++x,++y;
	}
	ans[n]=-a[n][n+1]/a[n][n];
	for(int i = n-1; i >= 1; --i) {
		double sum=a[i][n+1];
		for(int j = i+1; j <= n; ++j) sum+=ans[j]*a[i][j];
		ans[i]=-sum/a[i][i];
	}
}
int main() {
	scanf("%d%d", &n,&m);
	for(int i = 0; i < m; ++i) {
		int x,y,w;
		scanf("%d%d%d", &x,&y,&w);
		G[x].push_back({y,w});
		if(x!=y) G[y].push_back({x,w});
	}
	double sum=0;
	for(int i = 0; i <= 30; ++i) {
		solve(i);
		sum+=(1<<i)*1.0*ans[1];
	}
	printf("%.3f\n", sum);
	return 0;
}
