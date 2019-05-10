namespace _triangle{
struct triangle{
    point t0,t1,t2;
    triangle(point _t0 = point(0,0),point _t1 = point(0,0),point _t2 = point(0,0)):t0(_t0),t1(_t1),t2(_t2){}
    double area(){
        return fabs(across(t1-t0,t2-t1))/2;
    }
};
}
using namespace _triangle;
