template<class T, class Compare = std::less<T> >
class splay_tree {
private:
    struct node {
        T key;
        node *ch[2];
        Compare cmp;

        node() {}

        node(T key) : key(key) {
            ch[0] = ch[1] = NULL;
        }
    } *root;
    Compare cmp;

    void Deletetree(node *&t) {
        if (t == NULL) return;
        Deletetree(t->ch[0]);
        Deletetree(t->ch[1]);
        delete t;
        t = NULL;
    }
    node* Splayrotate(node *&t, T key) {
        if(t == NULL) return NULL;
        node *l, *r, *c, N;
        N.ch[0] = N.ch[1] = NULL;
        l = r = &N;
        while(true) {
            if(cmp(key, t->key)) {
                if(t->ch[0] == NULL) break;
                if(cmp(key, t->ch[0]->key)) {   // rotate right
                    c = t->ch[0];
                    t->ch[0] = c->ch[1];
                    c->ch[1] = t;
                    t = c;
                    if(t->ch[0] == NULL) break;
                }
                r->ch[0] = t;                   // link right
                r = t;
                t = t->ch[0];
            } else if(cmp(t->key, key)) {
                if(t->ch[1] == NULL) break;
                if(cmp(t->ch[1]->key, key)) {   // rotate left
                    c = t->ch[1];
                    t->ch[1] = c->ch[0];
                    c->ch[0] = t;
                    t = c;
                    if(t->ch[1] == NULL) break;
                }
                l->ch[1] = t;                   // link left
                l = t;
                t = t->ch[1];
            } else break;
        }
        l->ch[1] = t->ch[0];                    // assemble
        r->ch[0] = t->ch[1];
        t->ch[0] = N.ch[1];
        t->ch[1] = N.ch[0];
        return t;
    }
    void Insert(node *&t, T z) {
        node *y = NULL, *x = t;
        int d;
        while(x != NULL) {
            y = x;
            d = cmp(x->key, z);
            x = x->ch[d];
        }
        if(y == NULL) t = new node(z);
        else if(cmp(z, y->key)) y->ch[0] = new node(z);
        else y->ch[1] = new node(z);
    }

    node* Remove(node* &t, T key) {
        if(t == NULL || Search(t, key) == NULL) return NULL;// 查找键值为key的节点，找不到的话直接返回
        node *x = Splayrotate(t, key);// 将key对应的节点旋转为根节点
        if(t->ch[0] != NULL) {
            Splayrotate(t, t->ch[0]->key);// 将t的前驱节点旋转为根节点
            t->ch[1] = t->ch[1]->ch[1];// 移除t节点
        } else t = t->ch[1];
        delete x;
        x = NULL;
        return t;
    }

    node* Search(node *t, T key) {
        int d;
        while((t != NULL) && (t->key != key)) {
            d = cmp(t->key, key);
            t = t->ch[d];
        }
        return t;
    }
    node* FindMin_Max(node *t, int d) {
        while(t->ch[d] != NULL) {
            t = t->ch[d];
        }
        return t;
    }
    void Showitem(node *t, int key = -1, int d = -1) {
        if(t == NULL) return ;
        if(d==-1)
            cout << setw(2) << t->key << " is root" << endl;
        else
            cout << setw(2) << key << "'s " << (d == 1 ? "right" : " left") << " is " << setw(2) << t->key << endl;

        Showitem(t->ch[0], t->key, 0);
        Showitem(t->ch[1], t->key, 1);
    }
public:
    splay_tree() {
        root = NULL;
    }

    ~splay_tree() {
        Deletetree(root);
    }
    void splay(T x) {
        Splayrotate(root, x);
    }
    void insert(T x) {
        Insert(root, x);
        Splayrotate(root, x);
    }
    node* search(T x) {
        return Search(root, x);
    }
    node* findmin_max(int d = 0) {
        return FindMin_Max(root, d);
    }
    void remove(T x) {
        root = Remove(root, x);
    }
    void clear() {
        Deletetree(root);
    }
    void item() {
        Showitem(root);
    }
};
