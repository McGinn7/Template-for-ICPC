/**
 * N - 点数
 */
int et, dis[N], que[N], cur[N], head[N];
struct Edge {
	int s, t, v, nxt;
} e[N * N];
void addEdge(int s, int t, int v) {
	e[et].s = s, e[et].t = t, e[et].v = v, e[et].nxt = head[s], head[s] = et++;
	e[et].s = t, e[et].t = s, e[et].v = 0, e[et].nxt = head[t], head[t] = et++;
}
bool bfs(int S, int T, int n) {
	int qh = 0, qt = 0;
	for (int i = 0; i < n; ++i)
		dis[i] = -1;
	dis[S] = 0, que[qt++] = S;
	while (qh < qt) {
		for (int i = head[que[qh++]]; ~i; i = e[i].nxt)
			if (e[i].v > 0 && !~dis[e[i].t]) {
				dis[e[i].t] = 1 + dis[e[i].s];
				if (e[i].t == T)
					return true;
				que[qt++] = e[i].t;
			}
	}
	return false;
}
int dinic(int S, int T, int n) {
	int u, qt, maxFlow = 0;
	while (bfs(S, T, n)) {
		for (int i = 0; i < n; ++i)
			cur[i] = head[i];
		u = S, qt = 0;
		while (~cur[S]) {
			if (u != T && ~cur[u] && e[cur[u]].v > 0
					&& dis[u] + 1 == dis[e[cur[u]].t]) {
				que[qt++] = cur[u];
				u = e[cur[u]].t;
			} else if (u == T) {
				int tmp = INF;
				for (int i = qt - 1; i >= 0; --i)
					tmp = min(tmp, e[que[i]].v);
				for (int i = qt - 1; i >= 0; --i) {
					e[que[i]].v -= tmp;
					e[que[i] ^ 1].v += tmp;
					if (!e[que[i]].v)
						qt = i;
				}
				u = e[que[qt]].s;
				maxFlow += tmp;
			} else {
				while (u != S && !~cur[u])
					u = e[que[--qt]].s;
				cur[u] = e[cur[u]].nxt;
			}

		}
	}
	return maxFlow;
}
