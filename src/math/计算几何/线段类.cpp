#include <bits/stdc++.h>
using namespace std;
int cmp(double tmp) {
    if(fabs(tmp) < 1e-9) return 0;
    return tmp < 0 ? -1 : 1;
}
struct Segment { // 线段类
    struct Point { // 点类
        double x, y;
        Point(double x = 0, double y = 0):x(x), y(y) {}
        bool operator == (const Point &tmp) const {
            return cmp(tmp.x - x) == 0 && cmp(tmp.y - y) == 0;
        }
    } u, v; // 线段的起点和终点
    //两种构造函数
    Segment(Point u = 0, Point v = 0):u(u), v(v) {}
    Segment(double x = 0, double y = 0, double a = 0, double b = 0) :u(x, y), v(a, b) {}
    // 叉乘
    static double CrossProduct(Point i, Point j, Point k) { // i->k 叉乘 i->j
        return (k.x - i.x) * (j.y - i.y) - (k.y - i.y) * (j.x - i.x);
    }
    static double DotProduct(Point i, Point j, Point k) { // i->k 点乘 i->j
        return (k.x - i.x) * (j.x - i.x) - (k.y - i.y) * (j.y - i.y);
    }
    // 判断点是否在线上，这个判定函数不具有一般性，只有在叉乘为零时才能使用
    static bool OnSegment_(Segment l, Point c) {
        Point a = l.u, b = l.v;
        return c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) &&
               c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y);
    }
    static bool OnSegment(Segment l, Point c) { // 如果叉积等于0且点积小于0，说明在线段内部
        if(c == l.u || c == l.v) return true;
        return cmp(CrossProduct(l.u, l.v, c)) == 0 && cmp(DotProduct(c, l.u, l.v)) < 0;
    }
    // 判断两线段是否相交，只有严格不相交时才返回false(两线段不存在共点)
    static bool isIntersect(Segment a, Segment b) {
        double ab_u = CrossProduct(a.u, a.v, b.u);
        double ab_v = CrossProduct(a.u, a.v, b.v);
        double ba_u = CrossProduct(b.u, b.v, a.u);
        double ba_v = CrossProduct(b.u, b.v, a.v);
        if(ab_u * ab_v < 0 && ba_u * ba_v < 0) return true; // 如果两个线段相互跨越
        if(ab_u == 0 && OnSegment_(a, b.u)) return true; // 如果叉积为零，且点在线上
        if(ab_v == 0 && OnSegment_(a, b.v)) return true;
        if(ba_u == 0 && OnSegment_(b, a.u)) return true;
        return ba_v == 0 && OnSegment_(b, a.v);
    }
    // 返回线段的斜率(正切值)
    double tan() {
        double tmp = u.x - v.x;
        return tmp == 0.0 ? 1e9+7 : (u.y - v.y)/tmp;
    }
    // 在两线段不平行的前提下求线段交点
    static Point GetCrossPoint(Segment a, Segment b) {
        double tmpLeft, tmpRight, retx, rety;
        tmpLeft = (b.v.x - b.u.x) * (a.u.y - a.v.y) - (a.v.x - a.u.x) * (b.u.y - b.v.y);
        tmpRight = (a.u.y - b.u.y) * (a.v.x - a.u.x) * (b.v.x - b.u.x) +
                b.u.x * (b.v.y - b.u.y) * (a.v.x - a.u.x) -
                a.u.x * (a.v.y - a.u.y) * (b.v.x - b.u.x);
        retx = tmpRight / tmpLeft;
        tmpLeft = (a.u.x - a.v.x) * (b.v.y - b.u.y) - (a.v.y - a.u.y) * (b.u.x - b.v.x);
        tmpRight = a.v.y * (a.u.x - a.v.x) * (b.v.y - b.u.y) +
                (b.v.x- a.v.x) * (b.v.y - b.u.y) * (a.u.y - a.v.y) -
                b.v.y * (b.u.x - b.v.x) * (a.v.y - a.u.y);
        rety = tmpRight / tmpLeft;
        return {retx, rety};
    }
};

int main() {
    cout << Segment::isIntersect(Segment(0,0,1,1), Segment(0,2,2,0)) << endl; // true
    cout << Segment::isIntersect(Segment(0,0,1,1), Segment(1,1,2,2)) << endl; // true
    cout << Segment::isIntersect(Segment(0,0,2,1), Segment(1,0,6,3)) << endl; // false
    Segment a(0, 0, 1, 1), b(1, 1, 2, 2);
    if(a.tan() == b.tan()) cout << -1 << endl;
    else {
        Segment::Point tmp = Segment::GetCrossPoint(a, b);
        cout << tmp.x << ' ' << tmp.y << endl;
    }
    return 0;
}