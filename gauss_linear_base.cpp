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

struct Gauss {
	int cnt;
	ll st, lb[66];
	void init() {
		cnt = 0, st = 0;
		rep(i, 0, 61) lb[i] = 0;
	}
	void add(ll w) {
		st |= w;
		for (int i = 60; i >=0; --i) {
			if ((w >> i & 1) && !lb[i]) {
				lb[i] = w, ++cnt;
				break;
			}
			w = min(w, w ^ lb[i]);
		}
	}
} G;