// time Complexity O(log(n))
int kth(int n, int m, int k)
{
	if (m == 1) return k;
	for (k = k*m+m-1; k >= n; k = k-n+(k-n)/(m-1));
		return k;
}