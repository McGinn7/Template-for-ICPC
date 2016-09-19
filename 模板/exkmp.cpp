int nx[N], ex[N];
void getnx(char a[]) {
	int n = strlen(a);
	nx[0] = n, nx[1] = 0;
	while (nx[1] + 1 < n && a[nx[1]] == a[nx[1] + 1])
		++nx[1];
	for (int i = 2, j = 1; i < n; ++i) {
		if (i + nx[i - j] < j + nx[j]) {
			nx[i] = nx[i - j];
		} else {
			int k = max(0, j + nx[j] - i);
			while (i + k < n && a[i + k] == a[k])
				++k;
			nx[j = i] = k;
		}
	}
}
void getex(char a[], char b[]) {
	int n = strlen(a), m = strlen(b);
	getnx(b);
	ex[0] = 0;
	while (ex[0] < min(n, m) && a[ex[0]] == b[ex[0]])
		++ex[0];
	for (int i = 1, j = 0; i < n; ++i)
		if (i + nx[i - j] < j + ex[j]) {
			ex[i] = nx[i - j];
		} else {
			int k = max(0, j + ex[j] - i);
			while (i + k < min(n, m) && a[i + k] == b[k])
				++k;
			ex[j = i] = k;
		}
}
