// Time O(V^0.5 * E)
// Left size - n, numbered from 1 to n
// Right size - m, numbered from 1 to m
struct Hopcroft {
	int n, m;
	int que[N], dx[N], dy[N], matx[N], maty[N];
	vector<int> e[N];
	void init(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n + 1) matx[i] = 0;
		rep(i, 1, m + 1) maty[i] = 0;
	}
	void addEdge(int u, int v) {
		e[u].pb(v);
	}
	int bfs() {
		int flag = 0, qh = 0, qt = 0;
		rep(i, 1, m + 1) dy[i] = 0;
		rep(i, 1, n + 1) {
			dx[i] = 0;
			if (!matx[i]) que[qt++] = i;
		}
		while (qh < qt) {
			int u = que[qh++];
			rep(i, 0, sz(e[u])) {
				int v = e[u][i];
				if (dy[v]) continue;
				dy[v] = dx[u] + 1;
				if (!maty[v]) flag = true;
				else {
					dx[maty[v]] = dx[u] + 2;
					que[qt++] = maty[v];
				}
			}
		}
		return flag;
	}
	int dfs(int u) {
		rep(i, 0, sz(e[u])) {
			int v = e[u][i];
			if (dy[v] != dx[u] + 1) continue;
			dy[v] = 0;	
			if (!maty[v] || dfs(maty[v])) {
				matx[u] = v, maty[v] = u;
				return true;
			}
		}
		return false;
	}
	int run() {
		int ret = 0;
		while (bfs()) rep(i, 1, n + 1) if (!matx[i])
				ret += dfs(i);
		return ret;
	}
} G;

