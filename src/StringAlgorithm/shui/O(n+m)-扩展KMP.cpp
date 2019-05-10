void GetNext(string & T, int & m, int jump[]) {
    int a = 0, p = 0;
    jump[0] = m;
    for (int i = 1; i < m; i++) {
        if (i >= p || i + jump[i - a] >= p) {
            if (i >= p) p = i;
            while (p < m && T[p] == T[p - i]) p++;
            jump[i] = p - i, a = i;
        }
        else jump[i] = jump[i - a];
    }
}
void GetExtend(string & S, int & n, string & T, int & m, int extend[], int jump[]) {
    int a = 0, p = 0;
    GetNext(T, m, jump);
    for (int i = 0; i < n; i++) {
        if (i >= p || i + jump[i - a] >= p) { // i >= p 的作用：举个典型例子，S 和 T 无一字符相同
            if (i >= p) p = i;
            while (p < n && p - i < m && S[p] == T[p - i]) p++;
            extend[i] = p - i, a = i;
        }
        else extend[i] = jump[i - a];
    }
}
int main() {
    int jump[100];
    int extend[100];
    string S, T;
    int n, m;
    while (cin >> S >> T) {
        n = S.size();
        m = T.size();
        GetExtend(S, n, T, m, extend, jump);
        // 打印 jump
        cout << "next:   ";
        for (int i = 0; i < m; i++)
            cout << jump[i] << " ";
        // 打印 extend
        cout << "\nextend: ";
        for (int i = 0; i < n; i++)
            cout << extend[i] << " ";
        cout << endl << endl;
    }
    return 0;
}