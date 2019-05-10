template <typename type, typename compare = std::less<type>>
class monotony_queue { // 默认最大的在队首
    compare cmp;
    type data[maxn];
    int head, tail;
    int add(int num) { return (num + 1) % maxn; }
    int sub(int num) { return (num - 1 + maxn) % maxn; }
public:
    monotony_queue() { head = 0, tail = 0; }
    void clear() { head = 0, tail = 0; }
    void push(type val) {
        while (head != tail && cmp(data[sub(tail)], val)) tail = sub(tail);
        data[tail] = val, tail = add(tail);
    }
    void pop() { head = add(head); }
    bool empty() { return head == tail; }
    type front() { return data[head]; }
};