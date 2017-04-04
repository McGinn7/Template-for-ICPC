int p[N];
int solve(int a[], int b[]) { // 下标0~n-1
	p[0] = -1;
	for (int i = 1, j = -1; i < m; ++i) {
		while (j >= 0 && b[j + 1] != b[i])
			j = p[j];
		j += (b[j + 1] == b[i]);
		p[i] = j;
	}
	for (int i = 0, j = -1; i < n; ++i) {
		while (j >= 0 && b[j + 1] != a[i])
			j = p[j];
		j += (b[j + 1] == a[i]);
		if (j == m - 1) { // a[i - m + 1, i] = b[0, m-1]
			return i + 1 - m + 1;
			j = p[j]; // 继续匹配
		}
	}
	return -1;
}