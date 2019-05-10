#include <bits/stdc++.h>
const int maxn = int(1e5) + 7;
template<typename type, typename _Compare = std::less<type>>
class monotony_stack {
    _Compare cmp;
    type data[maxn];
    int cur;
public:
    monotony_stack() { cur = 0; }
    void clear() { cur = 0; }
    void push(type val) {
        while (cur && !cmp(data[cur], val)) cur--;
        data[++cur] = val;
    }
    type top() { return data[cur]; }
    type lower_top() { if (!empty()) return data[cur - 1]; }
    void pop() { if (!empty()) cur--; }
    bool empty() { return cur == 0; }
    int size() { return cur; }
};
int t, n, num[maxn], smaller[maxn];
monotony_stack<int> stack;
int main() {
    scanf("%d", &t);
    while (t--) {
        stack.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", num + i);
        for (int i = 1; i <= n; i++) {
            stack.push(num[i]);
            if (stack.size() > 1) smaller[num[i]] = stack.lower_top();
            else smaller[num[i]] = -1;
        }
        for (int i = 1; i <= n; i++) printf("%d%c", smaller[num[i]], i == n ? '\n' : ' ');
    }
}