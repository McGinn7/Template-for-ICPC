#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<set>
#include<map>
#include<queue>
#include<bitset>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i,l,r) for(int i=l;i<(r);++i)
#define per(i,l,r) for(int i=r-1;i>=(l);--i)
#define sz(x) ((int)((x).size()))
#define sqr(x) ((ll)(x)*(x))
#define all(x) (x).begin(),(x).end()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define de(x) cout << #x << " = " << x << endl;
#define debug(x) freopen(x".in", "r", stdin);
#define setIO(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
const ll LINF = 1e17 + 7;
const ul BASE = 33;
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-8;
ll kpow(ll a, ll b) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1)
			ret = ret * a;
	return ret;
}
//--------------head--------------
int n, m, a, b, mid;
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
			if (u != T && ~cur[u] && e[cur[u]].v > 0 && dis[u] + 1
					== dis[e[cur[u]].t]) {
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
vi edge[N];
int main() {
	int TT, S, T;
	scanf("%d", &TT);
	rep(cas, 0, TT) {
		scanf("%d%d", &n, &m);
		scanf("%d%d%d", &a, &b, &mid);
		et = 0;
		rep(i, 0, 2 * n + 2)
			edge[i].clear(), head[i] = -1;
		rep(i, 1, n + 1)
			if (i != mid)
				addEdge(i, i + n, 1);
		S = 0, T = 2 * n + 1;
		rep(i, 0, m) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x + n, y, 1);
			addEdge(y + n, x, 1);
		}
		addEdge(S, a, 1), addEdge(S, b, 1);
		addEdge(mid, mid + n, 2), addEdge(mid + n, T, 2);
		dinic(S, T, 2 * n + 2);
		for (int i = 0; i < et; i += 2)
			if (!e[i].v && e[i].s > S && e[i].s < T && e[i].t > S && e[i].t < T) {
				if (abs(e[i].s - e[i].t) != n) {
					if (e[i].s > n)
						e[i].s -= n;
					if (e[i].t > n)
						e[i].t -= n;
					edge[e[i].s].pb(e[i].t), edge[e[i].t].pb(e[i].s);
				}
			}
		int u = a, p = a;
		printf("%d", a);
		while (u != b) {
			rep(i, 0, sz(edge[u]))
				if (edge[u][i] != p) {
					p = u;
					u = edge[u][i];
					break;
				}
			printf(" %d", u);
		}
		puts("");
	}
	return 0;
}
