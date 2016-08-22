struct Gauss {
	static const int N = 305, P = 1e9 + 7;
	int a[N][N];
	int kpow(int a, int b) {
		ll r = 1;
		for (; b; b >>= 1, a = a * a % P)
			if (b & 1)
				r = r * a % P;
		return r;
	}
	int solve(int n, int m) {
		int i = 0, x = 0;
		for (; i < n && x < m; ++i, ++x) {
			int r = i;
			while (r < n && !a[r][x])
				++r;
			if (r < n) {
				if (r != i)
					rep(j, 0, m + 1)
						swap(a[r][j], a[i][j]);
//				rep(j, 0, n)
//					if (i != j && a[j][x])
//						for (int k = m; k >= x; --k)
//							a[j][k] = (a[j][k]
//									- 1ll * a[i][k] * a[j][x] % P
//											* kpow(a[i][x], P - 2) % P + P) % P;
				rep(j, 0, n)
					if (i != j && a[j][x])
						for (int k = m; k >= x; --k)
							a[j][k] -= a[i][k] * a[j][x] / a[i][x];
			} else
				--i;
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return m - i;
	}
	void output(int n, int m) {
		rep(i, 0, n)
		{
			rep(j, 0, m)
				printf("%d ", a[i][j]);
			puts("");
		}
	}
} G;
