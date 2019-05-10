namespace _line {
struct line {
    point a,b;
    line(point x=point(0,0),point y=point(0,0)):a(x),b(y) {}
    void input(){
        a.input();
        b.input();
    }
};
bool point_on_segment(point p,point s,point t) { ///1
    return cmp(across(p-s,t-s))==0&&cmp(dot(p-s,p-t))<=0;
}
bool parallel(line a,line b) {///判平行
    return !cmp(across(a.a-a.b,b.a-b.b));
}
point point_across_line(line l, point p) { ///点关于直线的对称点
    point p1 = l.a;
    point p2 = l.b;
    double _x, _y;
    if(cmp(p1.x - p2.x) == 0) {
        _x = 2 * p1.x - p.x;
        _y = p.y;
    } else if(cmp(p1.y - p2.y) == 0) {
        _x = p.x;
        _y = 2 * p1.y - p.y;
    } else {
        double k1 = (p1.y - p2.y) / (p1.x - p2.x);
        double b1 = p1.y - k1 * p1.x;
        double k2 = -1 / k1;
        double b2 = p.y - k2 * p.x;
        _x = (b2 - b1) / (k1 - k2);
        _y = k2 * _x + b2;
    }
    return point(2 * _x - p.x, 2 * _y - p.y);
}
bool segment_across_line(line a,line b){ ///判断线段和直线相交
    if(across(b.a-a.a,b.b-a.a)*across(b.a-a.b,b.b-a.b)>eps)
        return false;
    return true;
}
bool segment_across_segment(line l1,line l2){///线段和线段相交
    return
        max(l1.a.x,l1.b.x) >= min(l2.a.x,l2.b.x) &&
        max(l2.a.x,l2.b.x) >= min(l1.a.x,l1.b.x) &&
        max(l1.a.y,l1.b.y) >= min(l2.a.y,l2.b.y) &&
        max(l2.a.y,l2.b.y) >= min(l1.a.y,l1.b.y) &&
        cmp(across((l2.a-l1.a),(l1.b-l1.a)))*cmp(across((l2.b-l1.a),(l1.b-l1.a))) <= 0 &&
        cmp(across((l1.a-l2.a),(l2.b-l2.a)))*cmp(across((l1.b-l2.a),(l2.b-l2.a))) <= 0;
}
bool point_of_line_to_line(line a,line b,point &ret){///直线和直线的交点
    if(parallel(a,b)) return false;
    double s1 = across(a.a-b.a,b.b-b.a);
    double s2 = across(a.b-b.a,b.b-b.a);
    ret = point(s1*a.b-s2*a.a)/(s1-s2);
    return true;
}
}
using namespace _line;
