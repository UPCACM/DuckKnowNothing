#include <bits/stdc++.h>
const int maxn = int(1e6) + 7;
struct AC {
#define WIDTH 26
private:
    int size, root;
    struct Node { int end, fail, next[WIDTH]; } node[maxn];
    int Node() {
        size++;
        node[size].end = 0, node[size].fail = -1;
        for (int i = 0; i < WIDTH; i++) node[size].next[i] = -1;
        return size;
    }
public:
    AC() { size = 0, root = Node();}
    void clear() {
        size = 0;
        root = Node();
    }
    void insert(char *str, int t = 0) {
        for (t = root; *str; str++) {
            int pos = *str - 'a';
            if (node[t].next[pos] == -1) node[t].next[pos] = Node();
            t = node[t].next[pos];
        }
        node[t].end++;
    }
    void build_fail_pointer() {
        std::queue<int> que;
        for (int i = 0; i < WIDTH; i++) if (~node[root].next[i]) {
            que.push(node[root].next[i]);
            node[node[root].next[i]].fail = root;
        }
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (int i = 0; i < WIDTH; i++) {
                if (~node[cur].next[i]) {
                    int next = node[cur].next[i], fail = node[cur].fail;
                    que.push(next);
                    while (~fail) {
                        if (~node[fail].next[i]) {
                            node[next].fail = node[fail].next[i];
                            break;
                        }
                        fail = node[fail].fail;
                    }
                    if (fail == -1) node[next].fail = root;
                }
            }
        }
    }
    int ac_automaton(char *str) {
        int result = 0, cur = root;
        while (*str) {
            int pos = *str - 'a';
            if (~node[cur].next[pos]) {
                int next = node[cur].next[pos];
                while (next != root && node[next].end >= 0) {
                    result += node[next].end, node[next].end = -1;
                    next = node[next].fail;
                }
                cur = node[cur].next[pos], str++;
            } else {
                if (cur == root) str++;
                else cur = node[cur].fail;
            }
        }
        return result;
    }
} ac;
 
int t, n;
char str[maxn];
int main() {
    for (scanf("%d", &t); t; t--) {
        ac.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }
        scanf("%s", str);
        ac.build_fail_pointer();
        printf("%d\n", ac.ac_automaton(str));
    }
    return 0;
}

#include <bits/stdc++.h>
const int maxn = int(1e6) + 7;
struct AC {
#define TREE_WIDTH 26
private:
    struct Node {
        int end;
        Node *fail, *next[TREE_WIDTH];
        Node() {
            this->end = 0, this->fail = nullptr;
            for (int i = 0; i < TREE_WIDTH; i++) { this->next[i] = nullptr; }
        }
    } *root;
    void clear(Node *t) {
        for (int i = 0; i < TREE_WIDTH; i++) if (t->next[i]) clear(t->next[i]);
        delete t;
    }

public:
    AC() { root = new Node; }
    ~AC() { clear(root); }
    void clear() {
        clear(root);
        root = new Node;
    }
    void insert(char *s, int pos = 0) {
        Node *t = root;
        while (*s) {
            pos = *s - 'a';
            if (t->next[pos] == nullptr) t->next[pos] = new Node;
            t = t->next[pos];
            s++;
        }
        t->end++;
    }
    void build_fail_pointer() {
        std::queue<Node *> que;
        for (int i = 0; i < TREE_WIDTH; i++) if (root->next[i]) {
            que.push(root->next[i]);
            root->next[i]->fail = root;
        }
        Node *pre = nullptr, *son = nullptr, *fail = nullptr;
        while (!que.empty()) {
            pre = que.front();
            que.pop();
            for (int i = 0; i < TREE_WIDTH; i++) {
                if (pre->next[i]) {
                    son = pre->next[i];
                    que.push(son);
                    fail = pre->fail;
                    while (fail) {
                        if (fail->next[i]) {
                            son->fail = fail->next[i];
                            break;
                        }
                        fail = fail->fail;
                    }
                    if (!fail) son->fail = root;
                }
            }
        }
    }
    int ac_automaton(char *str) {
        int result = 0, pos;
        Node *pre = root, *cur = nullptr;
        while (*str) {
            pos = *str - 'a';
            if (pre->next[pos]) {
                cur = pre->next[pos];
                while (cur != root) {
                    if (cur->end >= 0) result += cur->end, cur->end = -1;
                    else break;
                    cur = cur->fail;
                }
                pre = pre->next[pos], str++;
            } else {
                if (pre == root) str++;
                else pre = pre->fail;
            }
        }
        return result;
    }
} ac;
int t, n;
char str[maxn];
int main() {
//    freopen("../in.txt", "r", stdin);
    for (scanf("%d", &t); t; t--) {
        ac.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }
        scanf("%s", str);
        ac.build_fail_pointer();
        printf("%d\n", ac.ac_automaton(str));
    }
    return 0;
}