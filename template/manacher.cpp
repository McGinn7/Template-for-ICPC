void manacher(int n, int a[], int l[]) { // l[] length = 2 * n
	l[0] = 1;
	for (int i = 1, j = 0; i + 1 < n << 1; ++i) {
		int p = i >> 1, q = i - p, r = (j + 1 >> 1) + l[j] - 1;
		l[i] = r < q ? 0 : min(r - q + 1, l[(j << 1) - i]);
		while (p - l[i] != -1 && q + l[i] != n && a[p - l[i]] == a[q + l[i]])
			++l[i];
		if (q + l[i] - 1 > r)
			j = i;
	}
}
//------------------------
int p[N];
void manacher(int n, char a[]) { // 1 ~ n, #a#b#d#a#
	int id, mx = 0;
	for (int i = 1; i <= n; ++i) {
		p[i] = (mx > i ? min(mx - i, p[2 * id - i]) : 1);
		while (i - p[i] >= 0 && i + p[i] <= n && a[i - p[i]] == a[i + p[i]])
			++p[i];
		if (i + p[i] > mx)
			id = i, mx = i + p[i];
	}
}


