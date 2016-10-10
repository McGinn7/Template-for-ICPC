void gauss() {
	int i = 0, x = 60;
	for (; i < n && x >= 0; ++i, --x) {
		int r = i;
		while (r < n && !(a[r] >> x & 1))
			++r;
		if (r >= n) {
			--i;
			continue;
		}
		if (r != i)
			swap(a[r], a[i]);
		rep(j, 0, n)
			if (i != j && (a[j] >> x & 1))
				a[j] ^= a[i];
	}
}
