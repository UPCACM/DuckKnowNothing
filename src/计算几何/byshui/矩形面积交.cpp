struct Rec {
    int x1, x2, y1, y2;
    void init() { scanf("%d%d%d%d", &x1, &y1, &x2, &y2); }
    int area() { return abs(x2 - x1) * abs(y2 - y1); }
    int intersection(const Rec &tmp) const {
        int tmpx = max((x2 - x1) + (tmp.x2 - tmp.x1) - (max(x2, tmp.x2) - min(x1, tmp.x1)), 0);
        int tmpy = max((y2 - y1) + (tmp.y2 - tmp.y1) - (max(y2, tmp.y2) - min(y1, tmp.y1)), 0);
        return tmpx * tmpy;
    }
};