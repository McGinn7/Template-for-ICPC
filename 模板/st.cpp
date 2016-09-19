int _min(int x, int y) {
	return min(x, y);
}
int _max(int x, int y) {
	return max(x, y);
}
struct ST {
	int lg[N], st[N][20];
	int (*get)(int, int);
	void build(int n, int a[], int (*_get)(int, int)) {
		get = _get, lg[1] = 0;
		rep(i, 2, n + 1) lg[i] = lg[i - 1] + (i == (i & -i));
		rep(i, 0, n) st[i][0] = a[i];
		for (int j = 1; (1 << j) <= n; ++j)
			for (int i = 0; i + (1 << j) <= n; ++i)
				st[i][j] = get(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	int qry(int l, int r) {
		if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		return get(st[l][k], st[r + 1 - (1 << k)][k]);
	}
} st[2];
