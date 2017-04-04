struct Edge {
	int s, t;
	ll w;
	Edge() {
	}
	Edge(int _s, int _t, ll _w) {
		s = _s, t = _t, w = _w;
	}
} e[N * N];
ll in[N];
int id[N], pre[N], vis[N];
bool liuzhu(int n, int m, int rt, ll &ans) {
	ans = 0;
	while (true) {
		rep(i, 0, n)
			in[i] = INF;
		rep(i, 0, m)
			if (e[i].s != e[i].t && e[i].w < in[e[i].t])
				in[e[i].t] = e[i].w, pre[e[i].t] = e[i].s;
		rep(i, 0, n)
			if (i != rt && in[i] >= INF)
				return false;
		int nn = 0;
		rep(i, 0, n)
			id[i] = vis[i] = -1;
		in[rt] = 0;
		rep(i, 0, n)
		{
			ans += in[i];
			int v = i;
			while (v != rt && id[v] == -1 && vis[v] != i)
				vis[v] = i, v = pre[v];
			if (v != rt && id[v] == -1) {
				for (int u = pre[v]; u != v; u = pre[u])
					id[u] = nn;
				id[v] = nn++;
			}
		}
		if (!nn)
			break;
		rep(i, 0, n)
			if (id[i] == -1)
				id[i] = nn++;
		rep(i, 0, m)
		{
			int v = e[i].t;
			e[i].s = id[e[i].s], e[i].t = id[e[i].t];
			if (e[i].s != e[i].t)
				e[i].w -= in[v];
		}
		n = nn, rt = id[rt];

	}
	return true;
}
