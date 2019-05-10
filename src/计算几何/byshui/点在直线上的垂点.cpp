Point ptoline(Point p, Point line1, Point line2) { // 点在直线上的垂点
    Point t = p;
    t.x += line1.y - line2.y, t.y += line2.x - line1.x;
    return intersection(p, t, line1, line2); // 两直线交点
}