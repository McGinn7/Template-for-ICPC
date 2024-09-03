// n - #vertexes, m - #edges
// Main idea: set direction for every undirected edge, 
// so that every degree(vertex) <= sqrt(m) in new directed graph.
// Key step: add u→v if (degree(u), u) < (degree(v), v).
void triangle() {
	rep(i, 0, m) {
		int u = edges[0][i], v = edges[1][i];
		if (make_pair(dgr[u], u) > make_pair(dgr[v], v))
			swap(u, v);
		d[u].emplace_back(v);
	}
	fill(mark, mark + n, false);
	rep(i, 0, m) {
		int u = edges[0][i], v = edges[1][i];
		for (auto w : d[u]) mark[w] = true;		
		for (auto w : d[v]) if (mark[w]) {
			// find triangle (u, v, w)
		}
		for (auto w : d[u]) mark[w] = false;
	}
}
