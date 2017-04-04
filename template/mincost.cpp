struct MinCost {
	const static int N = 2e4 + 7;
	const static int M = 1e5 + 7;
	struct Edge {
		int s, t, cap, cost, nxt;
		Edge() {
		}
		Edge(int _s, int _t, int _cap, int _cost, int _nxt) {
			s = _s, t = _t, cap = _cap, cost = _cost, nxt = _nxt;
		}
	} e[M * 2];
	ll dis[N];
	queue<int> que;
	int n, et, pre[N], vis[N], head[N];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(head[0]) * n);
	}
	void addEdge(int s, int t, int cap, int cost) {
		e[et] = Edge(s, t, cap, cost, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, -cost, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		rep(i, 0, n)
			pre[i] = -1, dis[i] = LINF, vis[i] = false;
		dis[S] = 0, vis[S] = true, que.push(S);
		while (!que.empty()) {
			int u = que.front();
			assert(dis[u] >= 0);
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].t;
				if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
					pre[v] = i, dis[v] = dis[u] + e[i].cost;
					if (!vis[v])
						vis[v] = true, que.push(v);
				}
			}
			vis[u] = false, que.pop();
		}
		return dis[T] != LINF;
	}
	pair<ll, ll> solve(int S, int T) {
		ll maxflow = 0, mincost = 0;
		while (bfs(S, T)) {
			ll flow = INF;
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				flow = min(flow, (ll) e[i].cap);
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				e[i].cap -= flow, e[i ^ 1].cap += flow;
			maxflow += flow, mincost += flow * dis[T];
		}
		return mp(maxflow, mincost);
	}
} G;
