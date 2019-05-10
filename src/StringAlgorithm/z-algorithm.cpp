// z[i]代表ｉ开始的后缀与整个串的最长公共前缀
// time complexity O(n)
const int maxn=100050;
struct z_Algorithm {
	int z[maxn];
	void init(char *str,int n) {
		z[1]=n;
		for(int i = 2,l=0,r=0; i <= n; ++i) {
			if(i<=r) z[i]=min(z[i-l+1],r-i+1);
			else z[i]=0;
			while(str[i+z[i]]==str[1+z[i]]) ++z[i];
			if(i+z[i]-1>r) r=i+z[i]-1,l=i;
		}
	}
};
