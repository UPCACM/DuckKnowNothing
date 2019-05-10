#include <bits/stdc++.h>
struct Point {
    double x, y;
} point[int(2e5) + 7];

double dist(Point p1, Point p2) { // 两点间距离
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double cross_product(Point p0, Point p1, Point p2) { // 叉乘
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool cmp(const Point &p1, const Point &p2) { // 按极角排序
    double temp = cross_product(point[0], p1, p2);
    if (fabs(temp) < 1e-6) return dist(point[0], p1) < dist(point[0], p2);
    return temp > 0;
}

vector<Point> graham_scan(int n) { // 求凸包
    vector<Point> ch;
    int top = 2;
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (point[i].y < point[index].y || (point[i].y == point[index].y && point[i].x < point[index].x)) index = i;
    }
    swap(point[0], point[index]);
    ch.push_back(point[0]);
    sort(point + 1, point + n, cmp);
    ch.push_back(point[1]);
    ch.push_back(point[2]);
    for (int i = 3; i < n; ++i) {
        while (top > 0 && cross_product(ch[top - 1], point[i], ch[top]) >= 0) {
            --top;
            ch.pop_back();
        }
        ch.push_back(point[i]);
        ++top;
    }
    return ch;
}

double rotating_caliper(vector<Point> v) { // 旋转卡壳求凸包最大直径
    double max_dis = 0.0;
    int n = int(v.size());
    if (n == 2) max_dis = dist(v[0], v[1]);
    else {
        v.push_back(v[0]);
        int j = 2;
        for (int i = 0; i < n; ++i) {
            while (cross_product(v[i], v[i + 1], v[j]) < cross_product(v[i], v[i + 1], v[j + 1])) {
                j = (j + 1) % n;
            }
            max_dis = max(max_dis, max(dist(v[j], v[i]), dist(v[j], v[i + 1])));
        }
    }
    return max_dis;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &point[i].x, &point[i].y);
    printf("%lf\n", rotating_caliper(graham_scan(n)));
    return 0;
}