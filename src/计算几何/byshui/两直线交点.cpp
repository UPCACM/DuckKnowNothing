Point intersection(Point u1, Point u2, Point v1, Point v2) {
    Point ret = u1;
    double tmp = ((u1.x - v1.x) * (v1.y - v2.y) - (u1.y - v1.y) * (v1.x - v2.x))
                / ((u1.x - u2.x) * (v1.y - v2.y) - (u1.y - u2.y) * (v1.x - v2.x));
    ret.x += (u2.x - u1.x) * tmp;
    ret.y += (u2.y - u1.y) * tmp;
    return ret;
}