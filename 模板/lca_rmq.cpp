struct LCA_RMQ {
	// N - 点数
	int L, lg[N * 2], dep[N * 2], lft[N * 2], st[N * 2][20];
	int rmin(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	void dfs(const vi e[], int u, int p) {
		lft[u] = L, st[L++][0] = u;
		rep(i, 0, sz(e[u]))
			if (e[u][i] != p)
				dep[e[u][i]] = dep[u] + 1, dfs(e, e[u][i], u), st[L++][0] = u;
	}
	// e - 邻接表, rt - 根
	void build(const vi e[], int rt) {
		L = 0, dfs(e, rt, -1);
		lg[1] = 0;
		rep(i, 2, N << 1)
			lg[i] = lg[i - 1] + (i == (i & -i));
		rep(j, 1, 20)
		{
			int lim = L + 1 - (1 << j);
			rep(i, 0, lim)
				st[i][j] = rmin(st[i][j - 1], st[i + (1 << j >> 1)][j - 1]);
		}
	}
	int lca(int x, int y) {
		x = lft[x], y = lft[y];
		if (x > y)
			swap(x, y);
		int k = lg[y - x + 1];
		return rmin(st[x][k], st[y + 1 - (1 << k)][k]);
	}
} R;
