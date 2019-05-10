#include <cstdio>
#include <functional>
const int maxn = 1e6;
template <typename T>
struct BasicZKW {
	T tree[maxn * 2];
	int n;
	std::function<T(T, T)> op;

	void init(int n_, const std::function<T(T, T)> &op_) { n = n_, op = op_; }
	T& operator[] (int idx) { return tree[idx + n]; }//[0, n)

	void build() {
		for(int i = n - 1; i > 0; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int p, T val) {//a[p] = val
		tree[p += n] = val;
		for(p >>= 1; p > 0; p >>= 1) tree[p] = op(tree[p << 1], tree[p << 1 | 1]);
	}
	T query(int l, int r) {//[l, r]
		T res = tree[r += n];
		for(l += n; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = op(res, tree[l++]);
			if(r & 1) res = op(res, tree[--r]);
		}
		return res;
	}
};
BasicZKW<int> zkw;
int main() {
	zkw.init(5, [](int x, int y)->int{return x + y;});
	for(int i = 0; i < 5; i++) zkw[i] = i;
	zkw.build();
	printf("%d\n", zkw.query(0, 4));
	zkw.update(0, 1);
	printf("%d\n", zkw.query(0, 4));
	return 0;
}
