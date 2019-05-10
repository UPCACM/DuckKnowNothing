// 定义在<numeric>中，作用有两个，1.累加求和 2.自定义类型数据的处理
#include <numeric>
/* 累加求和 */
int sum = std::accumulate(vec.begin(), vec.end() , 42);
// 三个形参: 前两个指定要累加的元素范围，第三个形参是累加的初值。
string sum = accumulate(vec.begin(), vec.end(), string(""));
// 把vec里的所有string都连接起来

/*自定义数据类型的处理*/
struct Grade {
	string name;
	int grade;
} subject[2] = {{"English", 80}, {"Biology", 70}};

int main() {
	int sum = accumulate(subject, subject + 2, 0, [](int tmp, Grade b){return a + b.grade; });
	cout << sum << endl;
	return 0;
}