struct Hash {
	const static int H = 1e4 + 7, N = 1e6 + 7;
	int n, nxt[N], head[H];
	ll st[N], cnt[N];
	void init() {
		n = 0, memset(head, -1, sizeof(head));
	}
	void ins(ll _st, ll _cnt) {
		int p = _st % H;
		for (int i = head[p]; ~i; i = nxt[i])
			if (st[i] == _st) {
				cnt[i] += _cnt;
				return;
			}
		st[n] = _st, cnt[n] = _cnt, nxt[n] = head[p], head[p] = n++;
	}
} hs[2];
int g[20][20];
int n, m, S, cod[20], col[20];
void decode(int a[], int n, ll st) {
	for (int i = n; i >= 0; --i, st >>= 3)
		a[i] = st & 7; // a[i] = st & ((1 << 3) - 1);
}
void shift(int a[], int n) {
	for (int i = n; i > 0; --i)
		a[i] = a[i - 1];
	a[0] = 0;
}
ll encode(int a[], int n, int y) {
	if (y == m)
		shift(a, n);
	ll id = 0, st = 0;
	memset(col, -1, sizeof(col)), col[0] = 0; // 注意独立插头
	for (int i = 0; i <= n; ++i) {
		if (col[a[i]] == -1)
			col[a[i]] = ++id;
		a[i] = col[a[i]];
		st = (st << 3) | a[i];
	}
	return st;
}
void blank(int x, int y, int t) {
	for (int i = 0; i < hs[t].n; ++i) {
		decode(cod, S, hs[t].st[i]);
		int L = cod[y - 1], U = cod[y];
		if (L && U) { // 独立-独立；独立-普通
			cod[y - 1] = cod[y] = 0;
			rep(j, 0, m + 1)
				if (cod[j] == U)
					cod[j] = L;
			hs[t ^ 1].ins(encode(cod, S, y), hs[t].cnt[i]);
		} else if (L || U) {
			if (g[x][y + 1]) {
				cod[y - 1] = 0, cod[y] = L | U;
				hs[t ^ 1].ins(encode(cod, S, y), hs[t].cnt[i]);
			}
			if (g[x + 1][y]) {
				cod[y - 1] = L | U, cod[y] = 0;
				hs[t ^ 1].ins(encode(cod, S, y), hs[t].cnt[i]);
			}
		} else {
			if (g[x][y + 1] && g[x + 1][y]) {
				cod[y - 1] = cod[y] = 14;
				hs[t ^ 1].ins(encode(cod, S, y), hs[t].cnt[i]);
			}
		}
	}
}
void block(int x, int y, int t) {
	for (int i = 0; i < hs[t].n; ++i) {
		decode(cod, S, hs[t].st[i]);
		hs[t ^ 1].ins(encode(cod, S, y), hs[t].cnt[i]);
	}
}
