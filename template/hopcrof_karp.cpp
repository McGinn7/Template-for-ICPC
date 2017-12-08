// Time O(V^0.5 * E)
// Left size - n, numbered from 1 to n
// Right size - m, numbered from 1 to m
struct Hopcroft {
	int n, m;
	int que[N], dw[N << 1], mat[N << 1];
	vector<int> e[N];
	void init(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n + m + 1) mat[i] = 0;
	}
	void addEdge(int u, int v) {
		e[u].pb(n + v);
	}
	int bfs() {
		int flag = 0, qh = 0, qt = 0;
		rep(i, 1, n + m + 1) dw[i] = 0;
		rep(i, 1, n + 1) if (!mat[i]) 
			que[qt++] = i;
		while (qh < qt) {
			int u = que[qh++];
			rep(i, 0, sz(e[u])) {
				int v = e[u][i];
				if (dw[v]) continue;
				dw[v] = dw[u] + 1;
				if (!mat[v]) flag = true;
				else {
					dw[mat[v]] = dw[u] + 2;
					que[qt++] = mat[v];
				}
			}
		}
		return flag;
	}
	int dfs(int u) {
		rep(i, 0, sz(e[u])) {
			int v = e[u][i];
			if (dw[v] != dw[u] + 1) continue;
			dw[v] = 0;
			if (!mat[v] || dfs(mat[v])) {
				mat[u] = v, mat[v] = u;
				return true;
			}
		}
		return false;
	}
	int run() {
		int ret = 0;
		while (bfs()) rep(i, 1, n + 1) if (!mat[i])
				ret += dfs(i);
		return ret;
	}
} G;

