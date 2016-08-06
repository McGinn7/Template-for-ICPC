vi e[N];
struct BCC {
	const static int N = 1e4 + 7;
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
						bcc[cnt].pb(sta[top]);
					bcc[cnt].pb(u), bcc[cnt].pb(v);
					++cnt;
				}
			} else if (dfn[v] != dfn[u] - 1 || src++) {
				low[u] = min(low[u], dfn[v]);
			}
		}
	}
	void run(int _n) {
		n = _n, cnt = top = 0;
		fill_n(dfn, n, 0), fill_n(bcc, n, vi());
		rep(i, 0, n)
			if (!dfn[i])
				dfs(i, 1);
	}
} G;
