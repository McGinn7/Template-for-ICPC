// n = |T|, m = |W|, index = [0, n)
lps[0] = -1;
for (int i = 1, j = -1; i < m; ++i) {
	while (j >= 0 && W[i] != W[j + 1])
		j = lps[j];
	j += W[i] == W[j + 1];
	lps[i] = j;
}
for (int i = 0, j = -1; i < n; ++i) {
	while (j >= 0 && T[i] != W[j + 1])
		j = lps[j];
	j += T[i] == W[j + 1];
	if (j == m - 1) {
		// match successfully
		j = lps[j];
	}
}