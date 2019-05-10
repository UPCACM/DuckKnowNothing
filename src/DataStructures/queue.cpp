template <typename type>
struct queue {
    const static int maxSize = 7;
    type data[maxSize];
    int head = 0, tail = 0;
    void push(type val) {
        data[tail] = val;
        tail = (tail + 1) % maxSize;
    }
    void pop() { head = (head + 1) % maxSize; }
    bool empty() { return head == tail; }
    int size() { return (tail - head + maxSize) % maxSize; }
    type front() { return data[head]; }
};