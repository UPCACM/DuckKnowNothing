//return is the index from 0
int getmin(char *s) {
    int i = 0, j = 1, n = int(strlen(s));
    while (i < n && j < n) {
        int k = 0;
        while (s[(i+k)%n] == s[(j+k)%n] && k < n) k++;
        if (k == n) return min(i, j);
        if (s[(i+k)%n] > s[(j+k)%n]) i = max(i+k+1, j+1);
        else j = max(j+k+1, i+1);
    }
    return min(i, j)%n;
}

int getmax(char *s) {
    int i = 0, j = 1, n = int(strlen(s));
    while (i < n && j < n) {
        int k = 0;
        while (s[(i+k)%n] == s[(j+k)%n] && k < n) k++;
        if (k == n) return min(i, j);
        if (s[(i+k)%n] < s[(j+k)%n]) i = max(i+k+1, j+1);
        else j = max(j+k+1, i+1);
    }
    return min(i, j)%n;
}