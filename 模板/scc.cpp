struct SCC {
	const static int N = 1e4 + 7, M = 1e5 + 7;
	struct Edge {
		int t, nxt;
		Edge() {

		}
		Edge(int _t, int _nxt) {
			t = _t, nxt = _nxt;
		}
	} e[M];
	vi scc[N];
	int n, et, cnt, tot, top, sta[N], vis[N], dfn[N], low[N], head[N];
	void addEdge(int s, int t) {
		e[et] = Edge(t, head[s]), head[s] = et++;
	}
	void dfs(int u) {
		sta[++top] = u, vis[u] = true;
		dfn[u] = low[u] = ++tot;
		for (int i = head[u]; ~i; i = e[i].nxt) {
			int v = e[i].t;
			if (dfn[v]) {
				if (vis[v])
					low[u] = min(low[u], dfn[v]);
			} else {
				dfs(v);
				low[u] = min(low[u], low[v]);
			}
		}
		if (low[u] == dfn[u]) {
			scc[cnt].clear();
			int v;
			do {
				v = sta[top--];
				scc[cnt].pb(v), vis[v] = false;
			} while (v != u);
			++cnt;
		}
	}
	void init(int _n) {
		n = _n, et = cnt = tot = top = 0;
		fill_n(dfn, n, 0), fill_n(vis, n, false), fill_n(head, n, -1);
	}
	void run() {
		rep(i, 0, n)
			if (!dfn[i])
				top = 0, dfs(i);
	}
} G;
