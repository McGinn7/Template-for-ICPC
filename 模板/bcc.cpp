vi e[N];
struct BCC {
	vi bcc[N];
	int n, cnt, top, sta[N], dfn[N], low[N];
	void dfs(int u, int dep) {
		int src = 0;
		sta[top++] = u, dfn[u] = low[u] = dep;
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (!dfn[v]) {
				dfs(v, dep + 1);
				low[u] = min(low[u], low[v]);
				if (low[v] >= dfn[u]) {
					while (sta[--top] != v)
						bcc[sta[top]].pb(cnt);
					bcc[u].pb(cnt), bcc[v].pb(cnt++);
				}
			} else if (dfn[v] != dfn[u] - 1 || src++) {
				low[u] = min(low[u], dfn[v]);
			}
		}
	}
	void run(int _n) {
		n = _n;
		cnt = top = 0;
		memset(dfn, 0, sizeof(dfn[0]) * n);
		memset(low, 0, sizeof(low[0]) * n);
		fill_n(bcc, n, vi());
		rep(i, 0, n)
			if (!dfn[i])
				dfs(i, 1);
	}
} G;
