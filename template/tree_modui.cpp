// prepare lca
int B; // block size, B = sqrt(n)
int dfs(int u, int p) {
	static int blocks = 0;	
	dep[u] = dep[p] + 1;
	dfn[u] = ++timeStamp;
	int size = 0;
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p)
			continue;
		size += dfs(v, u);
		if (size >= B) {
			++blocks;
			while (size--) bid[sta[top--]] = blocks;
		}
	}
	sta[++top] = u;
	if (u == 1) { // 1 is root
		++blocks;
		while (top) bid[sta[top--]] = blocks;
	}
	return size + 1;
}
void flip(int u) {
	// change status of u, if vis[u] remove else insert
}
void gao(int u, int v) {
	while (u != v) {
		if (dep[u] < dep[v]) swap(u, v);
		flip(u);
		u = f[u][0]; // direct father
	}
}
struct Query {
	int u, v, id, bid; // dfn[u] < dfn[v], bid = bid[u]
	bool operator<(const Query&q) const { // order(bid, dfn[v])
		if (bid != q.bid)
			return bid < q.bid;
		return dfn[v] < dfn[q.v];
	}
} q[M]; // M operations
int main() {
	sort(q, q + m);
	int u = 1, v = 1, lca = 1;
	flip(lca);
	rep(i, 0, m) {
		flip(lca);
		gao(u, q[i].u), gao(v, q[i].v);
		u = q[i].u, v = q[i].v;
		flip(lca = LCA(u, v));
		ans[q[i].id] = nowAns;
	}
	return 0;
}
