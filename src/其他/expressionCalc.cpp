#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
const int maxn=1000050;
char str[maxn];
ll f[maxn*5][2];
void mul(ll *a,ll *b,ll *c,char op) {
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			c[op=='&'?(i&j):(i|j)]+=a[i]*b[j];
			c[op=='&'?(i&j):(i|j)]%=MOD;
		}
	}
}
int precedence(char op) {
	if(op=='|') return 1;
	if(op=='&') return 2;
	if(op=='~') return 3;
	return 0;
}
void clr(stack<char>&op,stack<ll*>&var,int &tot) {
	if(op.top()=='~') swap(var.top()[0],var.top()[1]),op.pop();
	else {
		ll *v=var.top();var.pop();
		ll *u=var.top();var.pop();
		mul(u,v,f[++tot],op.top());
		op.pop();
		var.push(f[tot]);
	}
}
void calc(char *str) {
	int n=strlen(str+1);
	str[0]='(',str[n+1]=')';
	stack<char> op;
	stack<ll*> var;
	int tot=0;
	for(int i = 0; i <= n+1; ++i) {
		if(str[i]=='(') op.push(str[i]);
		else if(str[i]=='x') {
			while(isdigit(str[i+1])) ++i;
			++tot;
			f[tot][0]=f[tot][1]=1;
			var.push(f[tot]);
		}
		else if(str[i]==')') {
			while(!op.empty() && precedence(op.top())>0) {
				clr(op,var,tot);
			}
			assert(op.top()=='(');
			op.pop();
		}
		else if(str[i]=='~') op.push(str[i]);
		else {
			while(!op.empty() && precedence(str[i])<=precedence(op.top())) {
				if(precedence(str[i])==0) break;
				clr(op,var,tot);
			}
			op.push(str[i]);
		}
	}
	while(!op.empty()) {
		clr(op,var,tot);
	}
	assert(var.size());
	ll ans=var.top()[1];
	cout<<ans<<endl;
}
int main() {
	scanf("%s", str+1);
	calc(str);
	return 0;
}
