template <class T>
class Binary_Search_Tree {
private:
    int Capacity, Size, root;
    struct Base{
        T key;
        int num, l, r, pre;
        Base(){
            num = 0;
            l = r = pre = -1;
        }
    };
    Base *node;
    void Insert(int &x, T k, int p = -1) {
        if(x == -1) {
            x = ++Size;
            node[x].key = k;
            node[x].pre = p;
        }
        else if(k == node[x]) {
            node[x].num++;
        } else if(k < node[x].key) {
            Insert(node[x].l, k, x);
        } else Insert(node[x].r, k, x);
    }
    void Insert_NonRecur(int &x, T k) {
        int f = -1, t = x;
        while(t != -1) {
            f = t;
            if(k == node[t].key) node[t].num++;
            else if(k < node[t].key) t = node[t].l;
            else t = node[t].r;
        }
        node[++Size].key = k;
        node[Size].l = node[Size].r = -1;
        node[Size].pre = f;
        if(f == -1) x = Size;
        else {
            if(k < node[f].key) {
                node[f].l = Size;
            } else {
                node[f].r = Size;
            }
        }
    }
    int Search(int rt, T k) {
        while(rt != -1 && k != node[rt].key) {
            if(k < node[rt].key) rt = node[rt].l;
            else rt = node[rt].r;
        }
        return rt;
    }
    T Minimum(int rt) {
        while(node[rt].l != -1) {
            rt = node[rt].l;
        }
        return rt;
    }
    T Maximum(int rt) {
        while(node[rt].r != -1) {
            rt = node[rt].r;
        }
        return rt;
    }
    int Successor(int rt) { //后继：查找给定结点在中序遍历中的后继结点
        if(node[rt].r != -1) {
            return Minimum(node[rt].r);
        }
        int f = node[rt].pre;
        while(f != -1 && node[f].r == rt) {
            rt = f;
            f = node[f].pre;
        }
        return f;
    }
    int Predecessor(int rt) { //前驱：查找给定结点在中序遍历中的前驱结点
        if(node[rt].l != -1) {
            return Maximum(node[rt].l);
        }
        int f = node[rt].pre;
        while(f != -1 && node[f].l == rt) {
            rt = f;
            f = node[f].pre;
        }
        return f;
    }
    void Delete(int &rt, int z) {
        if(node[z].l == -1 && node[z].r == -1) {
            if(node[z].pre != -1) {
                if(node[node[z].pre].l == z) {
                    node[node[z].pre].l = -1;
                } else node[node[z].pre].r = -1;
            } else {
                rt = -1;// 只剩一个结点的情况
            }
        } else if(node[z].l != -1 && node[z].r == -1) {
            node[node[z].l].pre = node[z].pre;
            if(node[z].pre != -1) {
                if(node[node[z].pre].l == z) node[node[z].pre].l = node[z].l;
                else node[node[z].pre].r = node[z].l;
            } else {
                rt = node[z].l;// 删除左斜单支树的根结点
            }
        } else if(node[z].l == -1 && node[z].r != -1) {
            node[node[z].r].pre = node[z].pre;
            if(node[z].pre != -1) {
                if(node[node[z].pre].l == z) node[node[z].pre].l = node[z].r;
                else node[node[z].pre].r = node[z].r;
            } else {
                rt = node[z].r;
            }
        } else {
            int s = Successor(z);
            node[z].key = node[s].key;
            Delete(rt, s);
        }
    }

public:
    Binary_Search_Tree (int capacity = 1007) {
        root = -1, Size = 0;
        Capacity = capacity;
        node = new Base[Capacity];
    }
    Binary_Search_Tree (T *arr, int len, int capacity = 1007) {
        root = -1, Size = 0;
        Capacity = capacity;
        node = new Base[Capacity];
        srand((unsigned int)(time(NULL)));
        for(int i=len-1 ; i>=0 ; i--) {
            int j = rand() % (i+1);
            Insert(root,arr[j]);
            swap(arr[j], arr[i]);
        }
    }
    void insert(T a) {
        Insert_NonRecur(root, a);
    }
};
