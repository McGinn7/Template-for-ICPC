const int N = 601;

int n, m, f[N], w[N], g[N][N];
bool vis[N];

int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

int argmax(int n, int *a, bool *v) {
	pair<int, int> rec(INT_MIN, 0);
	rep(i, 0, n) if (!v[i])
		rec = max(rec, make_pair(a[i], i));
	return rec.second;
}

int min_cut_phase(int A, int &s, int &t) {
	rep(i, 0, n) {
		w[i] = 0, vis[i] = (i != get(i));	
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
	f[get(t)] = get(s);
	rep(i, 0, n) {
		g[s][i] += g[t][i];
		g[i][s] += g[i][t];
	}
}

int stoer_wagner_mincut() {
	rep(i, 0, n) f[i] = i;

	int ans = INT_MAX;
	rep(i, 1, n) {
		int s, t, cut_of_the_phase;
		cut_of_the_phase = min_cut_phase(i - 1, s, t);
		if (cut_of_the_phase < ans) {
			ans = cut_of_the_phase;
			rep(j, 0, n) if (get(j) == get(t)) {
				// A
			} else {
				// B
			}
		}
		merge_nodes(s, t);
	}
	return ans;
}
