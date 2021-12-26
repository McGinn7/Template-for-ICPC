const int N = 601;

int n, m, w[N], g[N][N];
bool vis[N], used[N];

int argmax(int n, int *a, bool *v) {
	pair<int, int> rec(INT_MIN, 0);
	rep(i, 0, n) if (!v[i])
		rec = max(rec, make_pair(a[i], i));
	return rec.second;
}

int min_cut_phase(int A, int &s, int &t) {
	rep(i, 0, n) {
		w[i] = 0, vis[i] = used[i];	
	}
	rep(_, A, n) {
		s = t;
		t = argmax(n, w, vis);
		vis[t] = true;
		rep(i, 0, n) if (!vis[i]) w[i] += g[t][i];
	}
	return w[t];
}

void merge_nodes(int s, int t) {
	used[t] = true;
	rep(i, 0, n) {
		g[s][i] += g[t][i];
		g[i][s] += g[i][t];
	}
}

int stoer_wagner_mincut() {
	scanf("%d%d", &n, &m);
	rep(i, 0, m) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		--a, --b;
		g[a][b] += c;
		g[b][a] += c;
	}
	rep(i, 0, n) used[i] = false;

	int ans = INT_MAX;
	rep(i, 1, n) {
		int s, t;	
		ans = min(ans, min_cut_phase(i - 1, s, t));
		merge_nodes(s, t);
	}
	return ans;
}
