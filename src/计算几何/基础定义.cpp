///const
const double eps = 1e-8;
const int maxm = 1000+10;
const double pi = acos(-1.0);
///determain the sign
int cmp(double x) {
    if(fabs(x)<eps)
        return 0;
    if(x>0)
        return 1;
    return -1;
}
