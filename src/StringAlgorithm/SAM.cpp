const int maxn = int(1e5) + 7;
struct SAM {
    struct Node {
        int len, pre; // 到达当前状态的最大步, 当前状态的父亲
        std::map<int, int> next;
        void init(int _len, int _pre) { // 状态节点初始化
            len = _len, pre = _pre;
            next.clear();
        }
    } node[maxn << 1];
    int size, last;
    void init() { // sam初始化
        for (int i = 1; i < size; i++) node[i].next.clear();
        node[0].init(0, -1);
        size = 1, last = 0;
    }
    void extend(int ch) {
        int cur = size++, u = last;
        node[cur].len = node[last].len + 1;
        while (u != -1 && !node[u].next.count(ch)) {
            node[u].next[ch] = cur;
            u = node[u].pre;
        }
        if (u == -1) node[cur].pre = 0; // 到达虚拟节点
        else {
            int v = node[u].next[ch];
            if (node[v].len == node[u].len + 1) node[cur].pre = v; // 状态连续
            else {
                int clone = size++; // 拷贝
                node[clone] = node[v];
                node[clone].len = node[u].len + 1;
                while (u != -1 && node[u].next[ch] == v) {
                    node[u].next[ch] = clone; // 把指向v的全部替换为指向clone
                    u = node[u].pre;
                }
                node[v].pre = node[cur].pre = clone;
            }
        }
        last = cur; // 更新last
    }
} sam;