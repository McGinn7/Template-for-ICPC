#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = 1e10 + 7;
const int N = 4e3 + 7;
const int M = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
struct MaxFlow {
	int n, et, dis[N], que[N], cur[N], head[N];
	struct Edge {
		int s, t, v, nxt;
		Edge() {

		}
		Edge(int _s, int _t, int _v, int _nxt) {
			s = _s, t = _t, v = _v, nxt = _nxt;
		}
	} e[M * 2];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(int) * n);
	}
	void addEdge(int s, int t, int v) {
		e[et] = Edge(s, t, v, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		int qh = 0, qt = 0;
		memset(dis, -1, sizeof(int) * n);
		dis[S] = 0, que[qt++] = S;
		while (qh < qt) {
			for (int i = head[que[qh++]]; ~i; i = e[i].nxt)
				if (e[i].v && !~dis[e[i].t]) {
					dis[que[qt++] = e[i].t] = 1 + dis[e[i].s];
					if (e[i].t == T)
						return true;
				}
		}
		return false;
	}
	ll dinic(int S, int T) {
		int u, qt;
		ll maxflow = 0;
		while (bfs(S, T)) {
			memcpy(cur, head, sizeof(int) * n);
			u = S, qt = 0;
			while (~cur[S]) {
				if (u == T) {
					ll flow = LINF;
					for (int i = qt - 1; i >= 0; --i)
						flow = min(flow, (ll) e[que[i]].v);
					for (int i = qt - 1; i >= 0; --i) {
						e[que[i]].v -= flow, e[que[i] ^ 1].v += flow;
						if (!e[que[i]].v)
							qt = i;
					}
					maxflow += flow, u = e[que[qt]].s;
				} else if (~cur[u] && e[cur[u]].v
						&& dis[u] + 1 == dis[e[cur[u]].t]) {
					que[qt++] = cur[u];
					u = e[cur[u]].t;
				} else {
					while (u != S && !~cur[u])
						u = e[que[--qt]].s;
					cur[u] = e[cur[u]].nxt;
				}
			}
		}
		return maxflow;
	}
} G;
int n, m, L, pay[N], t[N], pro[N];
vector<int> e[N];
ll solve(int mxt) {
	int S = 0, T = n + m + 1, sum = 0;
	G.init(T + 1);
	rep(i, 0, m)
		sum += pro[i], G.addEdge(S, i + 1, pro[i]);
	rep(i, 0, n)
		G.addEdge(m + i + 1, T, pay[i]);
	rep(i, 0, m)
	{
		bool flag = true;
		rep(j, 0, sz(e[i]))
			if (t[e[i][j]] > mxt) {
				flag = false;
				break;
			}
		if (!flag) {
			sum -= pro[i];
			continue;
		}
		rep(j, 0, sz(e[i]))
			G.addEdge(i + 1, m + e[i][j] + 1, INF);
	}
	ll ret = G.dinic(S, T);
	return sum - ret;
}
int main() {
//	setIO("data");
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d%d", &n, &m, &L);
		rep(i, 0, n)
			scanf("%d%d", &pay[i], &t[i]);
		rep(i, 0, m)
		{
			int k;
			scanf("%d%d", &pro[i], &k), e[i].clear();
			rep(_k, 0, k)
			{
				int x;
				scanf("%d", &x);
				e[i].pb(x - 1);
			}
		}
		int l = *min_element(t, t + n), r = *max_element(t, t + n);
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			solve(mid) >= L ? r = mid : l = mid;
		}
		printf("Case #%d: ", cas + 1);
		ll maxpro = solve(l);
		if (maxpro >= L) {
			printf("%d %I64d\n", l, maxpro);
		} else {
			maxpro = solve(r);
			if (maxpro >= L) {
				printf("%d %I64d\n", r, maxpro);
			} else {
				puts("impossible");
			}
		}
	}
	return 0;
}