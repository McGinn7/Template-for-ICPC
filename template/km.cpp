// find a perfect matching with maximum total cost
// in bipartite graph G=(X,Y;E).
// if you want the total cost minimum, just negative
// cost.
template<typename T>
struct KuhnMunkres {
	int n, m, vis[N], pre[N], mth[N];
	T INF, Lx[N], Ly[N], slack[N], w[N][N];

	void init(int _n, int _m, T _INF) {
		n = _n, m = _m, INF = _INF;
		// modify weight of non-edge if need
		rep(i, 0, n) rep(j, 0, m) w[i][j] = -INF;
	}

	inline void addEdge(int u, int v, int wgh) {
		w[u][v] = wgh;
	}

	void find(int v) {
		rep(i, 0, m + 1) vis[i] = 0, slack[i] = INF;
		int u = m;
		for (mth[u] = v; mth[u] != -1; u = v) {
			vis[u] = 1;
			T d = INF;
			rep(i, 0, m) if (!vis[i]) {
				T att = Lx[mth[u]] + Ly[i] - w[mth[u]][i];
				// maintain feasible solution
				if (att < slack[i]) slack[i] = att, pre[i] = u;
				// find minimum d
				if (slack[i] < d) d = slack[v = i];
			}
			rep(i, 0, m + 1)
				if (vis[i]) Lx[mth[i]] -= d, Ly[i] += d;
				else slack[i] -= d;
		}
		// find a augmented path
		for(; u != m; u = pre[u]) mth[u] = mth[pre[u]];
	}

	T solve() {
		bool iswap = false;
		if (n > m) {
			rep(i, 0, n) rep(j, 0, min(i, m))
				swap(w[i][j], w[j][i]);
			iswap = true, swap(n, m);
		}
		fill(Lx, Lx + n, 0);
		fill(Ly, Ly + m, 0);
		fill(mth, mth + m, -1);
		rep(i, 0, n) find(i);

		T ret = 0;
		rep(i, 0, n) ret += Lx[i];
		rep(i, 0, m) ret += Ly[i];
		if (iswap)
			per(i, 0, max(n, m)) swap(Lx[i], Ly[i]);
		return ret;
	}
};
