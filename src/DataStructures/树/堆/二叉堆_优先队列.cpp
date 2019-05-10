#include <bits/stdc++.h>
template<class type, class Compare = std::less<type> >
class priority_queue {
private:
    type *Heap;// 数据
    int Capacity, Size;// 总的容量，实际容量
    Compare cmp;
    void filterdown(int start, int end) {// 最大堆的向下调整算法
        int index = start;
        int cur = index << 1;// 先指向左儿子
        type tmp = Heap[index];
        while (cur <= end) {
            if (cur < end && cmp(Heap[cur], Heap[cur + 1])) {// cur+1是右儿子
                cur++;// 如果右儿子比较大，就将cur指向右儿子
            }
            if (!cmp(tmp, Heap[cur])) break;//调整结束
            Heap[index] = Heap[cur];
            index = cur;
            cur <<= 1;
        }
        Heap[index] = tmp;
    }

    void filterup(int start) {// 最大堆的向上调整算法(从start开始向上直到1，调整堆)
        int cur = start;
        int pre = cur >> 1;
        type tmp = Heap[cur];
        while (cur > 1) {
            if (!cmp(Heap[pre], tmp)) break;
            Heap[cur] = Heap[pre];
            cur = pre;
            pre >>= 1;
        }
        Heap[cur] = tmp;
    }

    int getindex(type data) {// 返回data在二叉堆中的索引
        for (int i = 1; i <= Size; i++) if (Heap[i] == data) return i;
        return -1;
    }

    bool remove(type data) {// 删除最大堆中的data，成功返回true
        if (Size == 0) return false;
        int index = getindex(data);// 获取data在二叉堆中的索引
        if (index == -1) return false;
        Heap[index] = Heap[Size--];
        filterdown(index, Size);
        return true;
    }

    void print() {// 打印二叉堆
        for (int i = 1; i < Size; i++) std::cout << Heap[i] << ' ';
        std::cout << Heap[Size] << std::endl;
    }

public:
    priority_queue(int capactity = 1007) {  // capactity 最大容量
        Capacity = capactity;
        Size = 0;
        Heap = new type[capactity + 7];
    }

    ~priority_queue() { delete (Heap); }

    void pop() {
        if (Size == 0) return;
        Heap[1] = Heap[Size--];
        filterdown(1, Size);
    }

    type top() {
        if (Size == 0) exit(1);
        return Heap[1];
    }

    bool empty() { return Size == 0; }

    bool push(type data) {// 将data插入到二叉堆中
        if (Size == Capacity) return false;
        Heap[++Size] = data;
        filterup(Size);
        return true;
    }
};
