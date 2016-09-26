int find(int u) {
	int t = 1;
	q[0] = u, f[u] = -1;
	rep(h, 0, t)
	{
		u = q[h];
		msz[u] = 0, siz[u] = 1;
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i].fi;
			if (vis[v] || v == f[u])
				continue;
			f[v] = u, q[t++] = v;
		}
	}
	for (int h = t - 1; h >= 0; --h) {
		u = q[h];
		msz[u] = max(msz[u], t - siz[u]);
		if (msz[u] * 2 <= t)
			return u;
		if (~f[u]) {
			siz[f[u]] += siz[u];
			msz[f[u]] = max(msz[f[u]], siz[u]);
		}
	}
	return 0;
}
void dfs1(int u, int w, int d, int p) {
	cnt1 += w == 0;
	cnt2 += R[1ll * (m - w) * rpw[d] % m];
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i].fi;
		if (vis[v] || v == p)
			continue;
		dfs1(v, (1ll * 10 * w + e[u][i].se) % m, d + 1, u);
	}
}
void dfs2(int u, int w, int d, int p) {
	cnt1 += w == 0;
	++R[w];
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i].fi;
		if (vis[v] || v == p)
			continue;
		dfs2(v, (1ll * e[u][i].se * pw[d] + w) % m, d + 1, u);
	}
}
void solve(int u) {
	u = find(u);
	R.clear();
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i].fi;
		if (vis[v])
			continue;
		dfs1(v, e[u][i].se % m, 1, u);
		dfs2(v, e[u][i].se % m, 1, u);
	}
	reverse(e[u].begin(), e[u].end());
	R.clear();
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i].fi;
		if (vis[v])
			continue;
		dfs1(v, e[u][i].se % m, 1, u);
		dfs2(v, e[u][i].se % m, 1, u);
	}
	vis[u] = true;
	rep(i, 0, sz(e[u]))
		if (!vis[e[u][i].fi])
			solve(e[u][i].fi);
}