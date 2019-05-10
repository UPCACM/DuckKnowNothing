#include <iostream>
#include <random>
#include <fstream>
using namespace std;
int main() {
    ofstream fout;//定义流文件输出
    fout.open("test.out");//打开文件
    random_device rd;//定义一种随机数引擎（产生器）
    default_random_engine gen = default_random_engine(rd());//设置默认引擎
    uniform_int_distribution<int> dis1(1,10);//设置类型范围
    uniform_real_distribution<double> dis2(1,10);//设置类型范围
    auto rand1 = bind(dis1,gen);
    //调用rand1()或者是dis1(gen)来产生1到10之间的整数
    auto rand2 = bind(dis2,gen);
    //调用rand2()或者是dis2(gen)来产生1到10之间的浮点数
    fout << "Hello World!" << endl;
    fout.close();//关闭文件
    return 0;
}
