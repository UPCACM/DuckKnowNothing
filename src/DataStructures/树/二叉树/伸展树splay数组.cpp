#define L ch[x][0]
#define R ch[x][1]

const int maxn = int(3e5) + 7;
int ch[maxn][2], sz[maxn], pre[maxn], add[maxn], val[maxn], stk[maxn], root, tot, Size, top, num[maxn], n, m, k1, k2;
bool flip[maxn];

void pushdown(int x) {
    if (add[x]) {
        val[L] += add[x];
        val[R] += add[x];
        add[L] += add[x];
        add[R] += add[x];
        add[x] = 0;
    }
    if (flip[x]) {
        flip[L] ^= 1;
        flip[R] ^= 1;
        swap(L, R);
        flip[x] = false;
    }
}

void pushup(int x) {
    sz[x] = sz[L] + sz[R] + 1;
}

int get(int x) {
    return ch[pre[x]][1] == x;
}

void rotate(int &x, int d) {
    int y = pre[x], z = pre[y];
    pushdown(z);
    pushdown(y);
    pushdown(x);
    ch[y][d ^ 1] = ch[x][d];
    pre[ch[x][d]] = y;
    pre[x] = z;
    if (z != 0) ch[z][get(y)] = x;
    ch[x][d] = y;
    pre[y] = x;
    pushup(y);
}

void splay(int x, int g) {
    pushdown(x);
    int y, z, d;
    while (pre[x] != g) {
        y = pre[x], z = pre[y];
        pushdown(z);
        pushdown(y);
        pushdown(x);
        if (z == g) {
            rotate(x, get(x) ^ 1);
        } else {
            d = get(y);
            ch[y][d] == x ? rotate(y, d ^ 1) : rotate(x, d);
            rotate(x, d ^ 1);
        }
    }
    if (g == 0) root = x;
    pushup(x);
}

int find(int k) { // Find the kth point's number
    int x = root;
    while (true) {
        pushdown(x);
        if (sz[L] == k) break;
        if (sz[L] > k) x = L;
        else {
            k -= sz[L] + 1;
            x = R;
        }
    }
    return x;
}

void rotate_to_somewhere(int k, int g) { // rotate kth point to be g's child (right child usually)
    int x = find(k);
    splay(x, g);
}

void newnode(int &x, int v, int p) {
    if (top != 0) x = stk[top--];
    else x = ++tot;
    Size++;
    pre[x] = p;
    sz[x] = 1;
    L = R = add[x] = 0;
    val[x] = v;
    flip[x] = false;
}

void build(int &x, int l, int r, int p) {
    if (l > r) return;
    int m = (l + r) >> 1;
    newnode(x, num[m], p);
    build(L, l, m - 1, x);
    build(R, m + 1, r, x);
    pushup(x);
}

void init(int n) {
    Size = top = tot = 0;
    newnode(root, -1, 0);
    newnode(ch[root][1], -1, root);
    for (int i = 0; i < n; i++) scanf("%d", num + i);
    build(ch[ch[root][1]][0], 0, n - 1, ch[root][1]);
    pushup(ch[root][1]);
    pushup(root);
}

int erase(int k) { // erase the kth node
    rotate_to_somewhere(k, 0);
    rotate_to_somewhere(k - 1, root);
    int l = ch[root][0], r = ch[root][1], ret = val[root];
    stk[++top] = root;
    Size--;
    root = l;
    pre[l] = 0;
    ch[l][1] = r;
    if (r != 0) pre[r] = l;
    pushup(root);
    return ret;
}

void insert(int v, int k = 0) { // insert point v after the kth point
    rotate_to_somewhere(k, 0);
    int x, r = ch[root][1];
    newnode(x, v, root);
    ch[root][1] = x;
    ch[x][1] = r;
    if (r != 0) pre[r] = x;
    pushup(x);
    pushup(root);
}

void show(int x = root) {
    if (x == 0) return;
    pushdown(x);
    show(L);
    printf("%d ", val[x]);
    show(R);
}

void move(int d) {
    if (d == 1) {
        int v = erase(Size - 2);
        insert(v, 0);
    }
    else {
        int v = erase(1);
        insert(v, Size - 2);
    }
}

void reverse(int l, int r) {
    rotate_to_somewhere(l - 1, 0);
    rotate_to_somewhere(r + 1, root);
    flip[ch[ch[root][1]][0]] ^= 1;
    pushup(ch[root][1]);
    pushup(root);
}

void update(int l, int r, int k) {
    rotate_to_somewhere(l - 1, 0);
    rotate_to_somewhere(r + 1, root);
    val[ch[ch[root][1]][0]] += k; // whatch out there!!!
    add[ch[ch[root][1]][0]] += k;
    pushup(ch[root][1]);
    pushup(root);
}

int query() {
    return val[find(1)];
}
