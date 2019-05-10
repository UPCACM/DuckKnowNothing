template <class T, class Compare = std::less<T> >
class Treap {
private:
    struct treap {
        int size, fix;
        T key;
        Compare cmp;
        treap *ch[2];

        treap(T key) {
            size = 1;
            fix = rand();
            this->key = key;
            ch[0] = ch[1] = NULL;
        }

        int compare(T x) const {
            if (x == key) return -1;
            return cmp(x ,key) ? 0 : 1;
        }

        void Maintain() {
            size = 1;
            if (ch[0] != NULL) size += ch[0]->size;
            if (ch[1] != NULL) size += ch[1]->size;
        }
    }*root;
    Compare cmp;

    void Rotate(treap *&t, int d) {
        treap *k = t->ch[d ^ 1];
        t->ch[d ^ 1] = k->ch[d];
        k->ch[d] = t;
        t->Maintain();
        k->Maintain();
        t = k;
    }

    void Insert(treap *&t, T x) {
        if (t == NULL) t = new treap(x);
        else {
            //int d = t->compare(x);
            int d = cmp(x ,t->key) ? 0 : 1;
            Insert(t->ch[d], x);
            if (t->ch[d]->fix > t->fix) Rotate(t, d ^ 1);
        }
        t->Maintain();
    }

    void Delete(treap *&t, T x) {
        int d = t->compare(x);
        if (d == -1) {
            treap *tmp = t;
            if (t->ch[0] == NULL) {
                t = t->ch[1];
                delete tmp;
                tmp = NULL;
            } else if (t->ch[1] == NULL) {
                t = t->ch[0];
                delete tmp;
                tmp = NULL;
            } else {
                int k = t->ch[0]->fix > t->ch[1]->fix ? 1 : 0;
                Rotate(t, k);
                Delete(t->ch[k], x);
            }
        } else Delete(t->ch[d], x);
        if (t != NULL) t->Maintain();
    }

    bool Find(treap *t, int x) {
        while (t != NULL) {
            int d = t->compare(x);
            if (d == -1) return true;
            t = t->ch[d];
        }
        return false;
    }

    T Kth(treap *t, int k) {
        if (t == NULL || k <= 0 || k > t->size) return -1;
        if (t->ch[0] == NULL) {
            if (k == 1) return t->key;
            return Kth(t->ch[1], k - 1);
        }
        if (t->ch[0]->size >= k) return Kth(t->ch[0], k);
        if (t->ch[0]->size + 1 == k) return t->key;
        return Kth(t->ch[1], k - 1 - t->ch[0]->size);
    }

    int Rank(treap *t, int x) {
        int r;
        if (t->ch[0] == NULL) r = 0;
        else r = t->ch[0]->size;
        if (x == t->key) return r + 1;
        if (x < t->key) return Rank(t->ch[0], x);
        return r + 1 + Rank(t->ch[1], x);
    }

    treap* PreSuc(treap *t, int x, int d) {// d = 0 : 前驱 , d = 1 : 后驱
        treap * pre = NULL;
        while(t != NULL && t->v != x) {
            int k = t->compare(x);
            if(k == (d^1)) pre = t;
            t = t->ch[k];
        }
        t = t->ch[d];
        if(t == NULL) return pre;
        else {
            while(t->ch[d^1] != NULL) {
                t = t->ch[d^1];
            }
            return t;
        }
    }

    void Deletetreap(treap *&t) {
        if (t == NULL) return;
        if (t->ch[0] != NULL) Deletetreap(t->ch[0]);
        if (t->ch[1] != NULL) Deletetreap(t->ch[1]);
        delete t;
        t = NULL;
    }

    void Print(treap *t) {
        if (t == NULL) return;
        Print(t->ch[0]);
        cout << t->key << ' ';
        Print(t->ch[1]);
    }

public:
    Treap() {
        root = NULL;
    }
    ~Treap() {
        Deletetreap(root);
    }
    void insert(T x) {
        Insert(root, x);
    }
    void clear() {
        Deletetreap(root);
    }
    T kth(int x) {
        return Kth(root, x);
    }
    void print() {
        Print(root);
    }
    int size() {
        return root->size;
    }
};
