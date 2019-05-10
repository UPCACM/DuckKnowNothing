namespace _polygon {
struct polygon {
    int n;
    vector<point> a;
    polygon(int _n = 0) {///初始化
        a.resize(_n);
        n = _n;
    }
    double length() {///OK
        double sum = 0;
        a[n] = a[0];
        for(int i = 0; i<n; i++)
            sum+=(a[i+1]-a[i]).len();
        return sum;
    }
    double area() {///凸包面积
        double ret = 0;
        a[n] = a[0];
        for(int i = 0; i<n; i++) {
            ret+=across(a[i+1],a[i]);
        }
        return ret/2.0;
    }
    int point_in_polygon(point t) {///判断点是否在凸包内
        int num = 0;
        a[n] = a[0];
        for(int i = 0; i<n; i++) {
            if(point_on_segment(t,a[i],a[i+1]))
                return 2;///on
            int k = cmp(across(a[i+1]-a[i],t-a[i]));
            int d1 = cmp(a[i].y-t.y);
            int d2 = cmp(a[i+1].y-t.y);
            if(k>0&&d1<=0&&d2>0)
                num++;
            if(k<0&&d2<=0&&d1>0)
                num++;
        }
        return num!=0;
    }
    point mess_center() {///凸包重心
        point ans(0,0);
        if(cmp(area())==0)
            return ans;
        a[n] = a[0];
        for(int i = 0; i<n; i++) {
            ans = ans+(a[i]+a[i+1])*across(a[i+1],a[i]);
        }
        return ans/area()/6.0;
    }
    int border_point_num() {
        int ret = 0;
        a[n] = a[0];
        for(int i = 0; i<n; i++) {
            ret+=__gcd(abs(int(a[i+1].x-a[i].x)),abs(int(a[i+1].y-a[i].y)));
        }
        return ret;
    }
    int inside_point_num() {
        return int(area())+1-border_point_num()/2;
    }
};
bool cmp_less(const point &a,const point &b) {///OK
    ///is a lower or lefter than b
    return cmp(a.x-b.x)<0||(cmp(a.x-b.x)==0&&cmp(a.y-b.y)<0);
}
polygon convex_full(vector<point> las) {///求凸包
    polygon ret(2*las.size()+5);
    sort(las.begin(),las.end(),cmp_less);
    las.erase(unique(las.begin(),las.end()),las.end());
    int m = 0;
    int si = las.size();
    for(int i = 0; i<si; i++) {
        while(m>1&&cmp(across(ret.a[m-1]-ret.a[m-2],las[i]-ret.a[m-2]))<=0)
            m--;
        ret.a[m++] = las[i];
    }
    int k = m;
    for(int i = si-2; i>=0; i--) {
        while(m>k&&cmp(across(ret.a[m-1]-ret.a[m-2],las[i]-ret.a[m-2]))<=0)
            m--;
        ret.a[m++] = las[i];
    }
    ret.a.resize(m);
    ret.n = m;
    if(si>1){
        ret.a.resize(m-1);
        ret.n--;
    }
    return ret;
}
int point_in_polygon_logn(const polygon &a,const point &b) {///在logn时间内判断点是否在凸包内
    int n = a.a.size();
    point g = (a.a[0]+a.a[n/3]+a.a[(n<<1)/3])/3.0;
    int l = 0,r = n;
    while(l+1<r) {
        int mid = (l+r)>>1;
        if(cmp(across(a.a[l]-g,a.a[mid]-g))>0) {
            if(cmp(across(a.a[l]-g,b-g))>=0&&cmp(across(a.a[mid]-g,b-g))>=0)
                r = mid;
            else
                l = mid;
        } else {
            if(cmp(across(a.a[l]-g,b-g))<0&&cmp(across(a.a[mid]-g,b-g))>=0)
                l = mid;
            else
                r = mid;
        }
    }
    r%=n;
    int z = cmp(across(a.a[r]-b,a.a[l]-b)) - 1;
    if(z==-2)
        return 1;
    return z;
}
double convex_diameter(polygon &a,int &first,int &second){///凸包直径和对锺点的下标
    vector<point> &p = a.a;
    int n = p.size();
    double maxd = 0.0;
    if(n==1) {
        first = second = 0;
        return 0;
    }
    #define nex(i) ((i+1)%n)
    for(int i = 0,j = 1;i<n;i++){
        while(cmp( across(p[nex(i)]-p[i] , p[j]-p[i]) - across(p[nex(i)]-p[i],p[nex(j)]-p[i]) )<0)
            j = nex(j);
        double d = (p[i]-p[j]).len();
        if(d>maxd) {
            maxd = d;
            first = i,second = j;
        }
        d = (p[nex(i)]-p[nex(j)]).len();
        if(d>maxd){
            maxd = d;
            first = i,second = j;
        }
    }
    return maxd;
}
}
using namespace _polygon;
