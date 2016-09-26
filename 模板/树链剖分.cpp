int tot, w[N], s[N], dep[N], far[N], top[N], siz[N];
void dfs(int u, int p) {
	s[u] = -1, far[u] = p, siz[u] = 1;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].t;
		if (v == p)
			continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		siz[u] += siz[v];
		if (s[u] == -1 || siz[v] > siz[s[u]])
			s[u] = v;
	}
}
void DFS(int u, int rt, int p) {
	w[u] = ++tot, top[u] = rt;
	if (~s[u])
		DFS(s[u], rt, u);
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].t;
		if (v == p || v == s[u])
			continue;
		DFS(v, v, u);
	}
}
