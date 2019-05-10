// 下标从0开始，最长不下降子序列的话就改成upper_bound，大于改大于等于
int array[maxn], f[maxn]; // f[i]： 第i个位置最小可以是多少
int LIS() {
    f[0] = array[0];
    int len = 1;
    for(int i=1 ; array[i] ; i++) {
        if(array[i] > f[len-1]) f[len++] = array[i];
        else f[lower_bound(f, f+len, array[i]) - f] = array[i];
    }
    return len;
}