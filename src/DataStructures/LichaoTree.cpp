#include<bits/stdc++.h>
//O(nlogn)
using namespace std;
const int maxm = 1e5+10;
double s[maxm],p[maxm];
int tree[maxm<<2];
double f(int num,int x){
    return p[num]*(x-1)+s[num];
}
void add(int ind,int l = 1,int r = maxm,int buf = 1){
    if(l==r){
        if(f(ind,l) > f(tree[ind],l)) tree[buf] = ind;
        return ;
    }
    int mid = (l+r)>>1;
    if(p[tree[buf]]<p[ind]){// the pre line's k is lower than now
        if(f(ind,mid)>f(tree[buf],mid)){
            add(tree[buf],l,mid,buf<<1);
            tree[buf] = ind;
        }else add(ind,mid+1,r,buf<<1|1);
    }
    if(p[tree[buf]]>p[ind]){
        if(f(ind,mid)>f(tree[buf],mid)){
            add(tree[buf],mid+1,r,buf<<1|1);
            tree[buf] = ind;
        }else add(ind,l,mid,buf<<1);
    }
}
double query(int pos,int l = 1,int r = maxm,int buf = 1){
    if(l==r) return f(tree[buf],pos);
    int mid = (l+r)>>1;
    if(pos<=mid) return max(query(pos,l,mid,buf<<1),f(tree[buf],pos));
    else return max(query(pos,mid+1,r,buf<<1|1),f(tree[buf],pos));
}
int main(){
    int n;
    scanf("%d",&n);
    int cnt = 1;
    while(n--){
        char nouse[10];
        scanf("%s",nouse);
        if(nouse[0]=='P'){
            scanf("%lf%lf",s+cnt,p+cnt);//x = 1,y = s[cnt],k = p[cnt]
            add(cnt);
            cnt++;
        }else{
            int xxx;
            scanf("%d",&xxx);
            printf("%d\n",query(xxx));//x = xxx,y = query(xxx)
        }
    }
    return 0;
}
