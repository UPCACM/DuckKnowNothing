struct Circle { double x, y, r; };

double area(Circle a, Circle b) {
    double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    double mi = min(a.r, b.r);
    double ans;
    if (d > a.r + b.r || d == a.r + b.r)    ans = 0.0;
    else if (d < abs(a.r - b.r) || d == abs(a.r - b.r)) ans = acos(-1.0) * mi * mi;
    else {
        double a1, a2, S1, S2, S3, p = (a.r + b.r + d) / 2.0;
        a1 = acos((a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d));
        a2 = acos((b.r * b.r + d * d - a.r * a.r) / (2.0 * b.r * d));
        S1 = a1 * a.r * a.r, S2 = a2 * b.r * b.r;
        S3 = 2 * sqrt(p * (p - a.r) * (p - b.r) * (p - d));
        ans = S1 + S2 - S3;
    }
    return ans;
}