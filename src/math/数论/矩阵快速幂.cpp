const int maxn = 107;
int Matrixsize = 2, mod = int(1e9)+7;
struct Matrix {
    int m[maxn][maxn];
    Matrix(int x = 0) {
        memset(m, 0, sizeof m);
        if (x) for(int i = 0; i < Matrixsize; i++) m[i][i] = 1;
    }
    Matrix operator * (const Matrix tmp) const {
        Matrix ret = 0;
        for(int i=0 ; i<Matrixsize ; i++)
            for(int k=0 ; k<Matrixsize ; k++)
                if(m[i][k]) for(int j=0 ; j<Matrixsize ; j++)
                    ret.m[i][j] = ((1ll * m[i][k] * tmp.m[k][j]) % mod + ret.m[i][j]) % mod;
        return ret;
    }
    Matrix qpow(long long q) {
        Matrix ret = 1, tmp = *this;
        for( ; q ; q>>=1) {
            if(q & 1) ret = ret * tmp;
            tmp = tmp * tmp;
        } return ret;
    }
};


/**
 *矩阵快速幂成员函数版
 **/
const int maxn = 107;
int Matrixsize = 2, mod = int(1e9)+7;
struct Matrix {
    int m[maxn][maxn];
    Matrix(int i = 0) {
        memset(m, 0, sizeof m);
        if (i == 1) for (int I = 0; I < Matrixsize; I++) m[I][I] = 1;
    }
    Matrix operator * (const Matrix tmp) const {
        Matrix ret;
        long long x;
        for(int i=0 ; i<Matrixsize ; i++) {
            for(int j=0 ; j<Matrixsize ; j++) {
                x=0;
                for(int k=0 ; k<Matrixsize ; k++) {
                    x+=((long long)m[i][k] * tmp.m[k][j]) % mod;
                }
                ret.m[i][j] = int(x % mod);
            }
        }
        return ret;
    }
    Matrix operator+(const Matrix b) const {
        Matrix a = *this;
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                a.m[i][j] = (a.m[i][j] + b.m[i][j]) % mod;
        return a;
    }
    Matrix operator-(const Matrix b) const {
        Matrix a = *this;
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                a.m[i][j] = (a.m[i][j] - b.m[i][j]) % mod;
        return a;
    }
    Matrix operator-() const {
        Matrix tmp = *this;
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                tmp.m[i][j] = -tmp.m[i][j];
        return tmp;
    }
    void operator += (const Matrix tmp) const {
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                m[i][j] = (m[i][j] + tmp.m[i][j]) % mod;
    }
    bool operator != (const Matrix tmp) const {
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                if(m[i][j] != tmp.m[i][j]) return true;
        return false;
    }
    bool operator == (const Matrix tmp) const {
        for (int i = 0; i < Matrixsize; i++)
            for (int j = 0; j < Matrixsize; j++)
                if(m[i][j] != tmp.m[i][j]) return false;
        return true;
    }
    Matrix qpow(long long n) {
        Matrix ret = 1, tmp = *this;
        while (n > 0) {
            if (bool(n & 1)) ret = ret * tmp;
            tmp = tmp * tmp;
            n >>= 1;
        }
        return ret;
    }
    void show() {
        Matrix tmp = *this;
        for(int i=0 ; i<Matrixsize ; i++) {
            for(int j=0 ; j<Matrixsize-1 ; j++) cout << tmp.m[i][j] << ' ';
            cout << tmp.m[i][Matrixsize-1] << endl;
        }
        cout << endl;
    }
};

/**
 *矩阵快速幂原版
 **/
const int maxn = 110,mod = 1e9+7;
int n;

struct mat {
    int m[maxn][maxn];
};
mat unit;//unit 是单位矩阵，任何矩阵乘以单位矩阵都是这个矩阵本身

mat operator * (mat a, mat b) {
    mat ret;
    long long x;
    for(int i=0 ; i<n ; i++) {
        for(int j=0 ; j<n ; j++) {
            x=0;
            for(int k=0 ; k<n ; k++) {
                x+=((long long)a.m[i][k] * b.m[j][k]) % mod;
            }
            ret.m[i][j] = x%mod;
        }
    }
    return ret;
}

void init_unit() {
    for(int i=0 ; i<maxn ; i++) unit.m[i][i] = 1;
    return ;
};

mat qpow_mat(mat a, long long n) {
    mat ret = unit;
    while(n) {
        if(n&1) ret = ret*a;
        a = a*a;
        n >>= 1;
    }
    return ret;
}
