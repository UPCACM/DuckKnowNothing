struct treap {
    int v, info, fix, ch[2], size;

    treap() {}

    treap(int info, int v) : info(info), v(v) {
        ch[0] = ch[1] = -1;
        fix = rand();
        size = 1;
    }

    int compare(int x) {
        if (v == x) return -1;
        return x < v ? 0 : 1;
    }
} node[maxn];

int root, tot;

void Maintain(int t) {
    node[t].size = 1;
    if (node[t].ch[0] != -1) node[t].size += node[node[t].ch[0]].size;
    if (node[t].ch[1] != -1) node[t].size += node[node[t].ch[1]].size;
}

void Rotate(int &t, int d) {
    if (t == -1) return;
    int tmp = node[t].ch[d ^ 1];
    node[t].ch[d ^ 1] = node[tmp].ch[d];
    node[tmp].ch[d] = t;
    Maintain(t);
    Maintain(tmp);
    t = tmp;
}

void Insert(int &t, int info, int v) {
    if (t == -1) {
        t = ++tot;
        node[t] = treap(info, v);
    } else {
        //int d = node[t].compare(v);
        int d = v < node[t].v ? 0 : 1;
        Insert(node[t].ch[d], info, v);
        if (node[t].fix < node[node[t].ch[d]].fix) Rotate(t, d ^ 1);
    }
    Maintain(t);
}

int Find(int t, int v) {
    if (t == -1) return t;
    int d = node[t].compare(v);
    if (d == -1) return t;
    return Find(node[t].ch[d], v);
}

int Findmax(int t) {
    if (t == -1) return -1;
    while (node[t].ch[1] != -1) {
        t = node[t].ch[1];
    }
    return t;
}

int Findmin(int t) {
    if (t == -1) return -1;
    while (node[t].ch[0] != -1) {
        t = node[t].ch[0];
    }
    return t;
}

void Delete(int &t, int x) {
    if (t == -1) return;
    int k = node[t].compare(x);
    if (k == -1) {
        if (node[t].ch[0] != -1 && node[t].ch[1] != -1) {
            int d = node[node[t].ch[0]].fix < node[node[t].ch[1]].fix ? 0 : 1;
            Rotate(t, d);
            Delete(node[t].ch[d]);
        } else {
            if (node[t].ch[0] == -1) t = node[t].ch[1];
            else t = node[t].ch[0];
        }
    } else Delete(node[t].ch[k], x);
    if (t != -1) Maintain(t);
}

void Print(int t) {
    if (t == -1) return;
    Print(node[t].ch[0]);
    cout << node[t].v << ' ';
    Print(node[t].ch[1]);
}
