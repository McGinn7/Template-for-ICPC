struct Dcc {
	const static int N = 1e3 + 7, M = 1e5 + 7;
	struct Edge {
		int t, w, nxt;
		Edge() {
		}
		Edge(int _t, int _w, int _nxt) {
			t = _t, w = _w, nxt = _nxt;
		}
	} e[M << 1];
	vector<pair<int, int> > edge;
	bool bdg[M << 1], vis[M << 1];
	int n, et, tot, dfn[N], low[N], f[N], head[N];
	void init(int _n) {
		n = _n, et = 0, tot = 0;
		rep(i, 0, n)
			f[i] = i;
		memset(dfn, 0, sizeof(int) * n);
		memset(head, -1, sizeof(int) * n);
	}
	void addEdge(int s, int t, int w) {
		vis[et] = false, bdg[et] = false, e[et] = Edge(t, w, head[s]), head[s] =
				et++;
		vis[et] = false, bdg[et] = false, e[et] = Edge(s, w, head[t]), head[t] =
				et++;
	}
	int get(int x) {
		return x == f[x] ? x : f[x] = get(f[x]);
	}
	void dfs(int u) {
		dfn[u] = low[u] = ++tot;
		for (int i = head[u]; ~i; i = e[i].nxt) {
			if (vis[i])
				continue;
			vis[i] = vis[i ^ 1] = true; // 避免重边
			int v = e[i].t;
			if (!dfn[v]) {
				dfs(v);
				low[u] = min(low[u], low[v]);
				if (dfn[u] < low[v]) {
					bdg[i] = true;
				} else
					f[get(u)] = get(v);
			} else {
				f[get(u)] = get(v), low[u] = min(low[u], dfn[v]);
			}
		}
	}
	void run() {
		dfs(0);
		edge.clear();
		rep(u, 0, n)
			for (int i = head[u]; ~i; i = e[i].nxt)
				if (bdg[i]) {
					int v = e[i].t;
					edge.push_back(make_pair(get(u), get(v)));
				}
	}
} G;
