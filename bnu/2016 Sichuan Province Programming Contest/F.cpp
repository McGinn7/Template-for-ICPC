#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e15 + 7;
const int N = 1e5 + 207;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
//----------head-----------
struct FastIO {
	static const int S = 2621440;
	int wpos;
	char wbuf[S];
	FastIO() :
			wpos(0) {
	}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len)
			return -1;
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x;
	}
	inline int xint() {
		int s = 1, c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		if (c == '-')
			s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char *s) {
		int c = xchar();
		while (c <= 32)
			c = xchar();
		for (; c > 32; c = xchar())
			*s++ = c;
		*s = 0;
	}
	inline void wchar(int x) {
		if (wpos == S)
			fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(int x) {
		if (x < 0)
			wchar('-'), x = -x;
		char s[24];
		int n = 0;
		while (x || !n)
			s[n++] = '0' + x % 10, x /= 10;
		while (n--)
			wchar(s[n]);
	}
	inline void wstring(const char *s) {
		while (*s)
			wchar(*s++);
	}
	~FastIO() {
		if (wpos)
			fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;
int n, m, q, f[N], ans[N];
pii Q[N];
vector<int> nd, e[N];
struct Edge {
	int t, nxt;
	Edge() {
	}
	Edge(int _t, int _nxt) {
		t = _t, nxt = _nxt;
	}
} g[N << 1];
int et, head[N];
inline int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}
int tot, lg[N << 1], dep[N], dfn[N], st[N << 1][20];
void dfs(int u, int p) {
	dfn[u] = tot;
	st[tot++][0] = u;
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i];
		if (v == p)
			continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		st[tot++][0] = u;
	}
}
inline int rmin(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}
void init() {
	lg[1] = 0;
	rep(i, 2, N << 1)
		lg[i] = lg[i - 1] + (i == (i & -i));
	rep(j, 1, 20)
	{
		int lim = tot + 1 - (1 << j);
		rep(i, 0, lim)
			st[i][j] = rmin(st[i][j - 1], st[i + (1 << j >> 1)][j - 1]);
	}
}
int lca(int x, int y) {
	x = dfn[x], y = dfn[y];
	if (x > y)
		swap(x, y);
	int k = lg[y - x + 1];
	return rmin(st[x][k], st[y + 1 - (1 << k)][k]);
}
int dis[N], que[N];
void bfs(int u) {
	int h = 0, t = 0;
	que[t++] = u;
	while (h < t) {
		int u = que[h++];
		for (int i = head[u]; ~i; i = g[i].nxt) {
			int v = g[i].t;
			if (dis[v] == -1) {
				dis[v] = dis[u] + 1;
				que[t++] = v;
			}
		}
	}
}
inline void addEdge(int u, int v) {
	g[et] = Edge(v, head[u]), head[u] = et++;
	g[et] = Edge(u, head[v]), head[v] = et++;
}
int main() {
//	freopen("data.in", "r", stdin);
	n = io.xuint();
	m = io.xuint();
	q = io.xuint();
	rep(i, 1, n + 1)
		f[i] = i, head[i] = -1;
	rep(i, 0, m)
	{
		int u, v;
		u = io.xuint();
		v = io.xuint();
		if (u == v)
			continue;
		addEdge(u, v);
		if (get(u) != get(v)) {
			f[get(u)] = get(v);
			e[u].pb(v), e[v].pb(u);
		} else {
			nd.pb(u), nd.pb(v);
		}
	}
	sort(nd.begin(), nd.end());
	nd.erase(unique(nd.begin(), nd.end()), nd.end());
	tot = 0, dep[1] = 0;
	dfs(1, -1);
	init();
	rep(i, 0, q)
	{
		int u, v, c;
		u = io.xuint();
		v = io.xuint();
		Q[i] = mp(u, v);
		c = lca(u, v);
		ans[i] = dep[u] + dep[v] - (dep[c] << 1);
	}
	rep(i, 0, sz(nd))
	{
		rep(j, 1, n + 1)
			dis[j] = -1;
		dis[nd[i]] = 0;
		bfs(nd[i]);
		rep(j, 0, q)
			ans[j] = min(ans[j], dis[Q[j].first] + dis[Q[j].second]);
	}
	rep(i, 0, q)
		printf("%d\n", ans[i]);
	return 0;
}
