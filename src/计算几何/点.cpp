namespace _point {
struct point {
    double x,y;
    point(double _a = 0,double _b = 0):x(_a),y(_b) {}
    void input() {
        scanf("%lf%lf",&x,&y);
    }
    friend point operator+(const point &a,const point &b) {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator-(const point &a,const point &b) {
        return point(a.x-b.x,a.y-b.y);
    }
    friend bool operator==(const point &a,const point &b) {
        return cmp(a.x-b.x)==0&&cmp(a.y-b.y)==0;
    }
    friend point operator*(const point &a,const double &b) {
        return point(a.x*b,a.y*b);
    }
    friend point operator*(const double &a,const point &b) {
        return point(b.x*a,b.y*a);
    }
    friend point operator/(const point &a,const double &b) {
        return point(a.x/b,a.y/b);
    }
    double len() {
        return sqrt(x*x+y*y);
    }
	double angle(){
        return atan2(y,x);
    }
};
double across(const point &a,const point &b) {///叉积
    return a.x*b.y-a.y*b.x;
}
double dot(const point &a,const point &b) {///点积
    return a.x*b.x+a.y*b.y;
}
double dist(const point &a,const point &b) {///距离
    return (a-b).len();
}
point rotate_point(const point &p,double angle) {///旋转
    double tx = p.x,ty = p.y;
    return point(tx*cos(angle)-ty*sin(angle),tx*sin(angle)+ty*cos(angle));
}
}
using namespace _point;
