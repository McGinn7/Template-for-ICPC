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
