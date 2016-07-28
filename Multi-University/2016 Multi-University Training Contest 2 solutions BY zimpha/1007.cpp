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
#include<string>
#include<sstream>
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
const ll LINF = 1e18 + 7;
const ul BASE = 1e6 + 7;
const int N = 5e2 + 7;
const int M = 5e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-7;
ll kpow(ll a, ll b, ll mod) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1)
			ret = ret * a % mod;
	return ret;
}
//--------------head-------------
struct KM { // 最大权匹配
	int n, m; // 左边n个点，右边m个点，必须满足n<=m!
	bool vis[M];
	ll Lx[N], Ly[M], slack[M], g[N][M];
	int pre[M], left[M]; // left[i]和i匹配
	void init(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 0, n)
			rep(j, 0, m)
				g[i][j] = -LINF;
		memset(Lx, 0, sizeof(Lx[0]) * n);
		memset(Ly, 0, sizeof(Ly[0]) * m);
		memset(left, -1, sizeof(left[0]) * m);
	}
	void addEdge(int u, int v, ll val) {
		g[u][v] = val;
	}
	void go(int now) {
		rep(i, 0, m + 1)
			vis[i] = false, slack[i] = LINF;
		left[m] = now;
		int u = m;
		while (~left[u]) {
			vis[u] = true;
			ll d = LINF;
			int v;
			rep(i, 0, m)
				if (!vis[i]) {
					ll tmp = Lx[left[u]] + Ly[i] - g[left[u]][i];
					if (tmp < slack[i])
						slack[i] = tmp, pre[i] = u;
					if (slack[i] < d)
						d = slack[v = i];
				}
			rep(i, 0, m + 1)
				if (vis[i])
					Lx[left[i]] -= d, Ly[i] += d;
				else
					slack[i] -= d;
			u = v;
		}
		while (u != m)
			left[u] = left[pre[u]], u = pre[u];
	}
	ll run() {
		rep(i, 0, n)
			go(i);
		ll ans = 0;
		rep(i, 0, n)
			ans += Lx[i];
		rep(i, 0, m)
			ans += Ly[i];
		return ans;
	}
} km;
int n, m, col[N], vis[N];
vi e[N];
char nxtChar() {
	char ch;
	while ((ch = getchar()) != '0' && ch != '1')
		;
	return ch;
}
int dis[N][N];
queue<int> que;
void spfa(int u, int D[]) {
	while (!que.empty())
		que.pop();
	rep(i, 1, n + 1)
		D[i] = INF, vis[i] = false;
	D[u] = 0, vis[u] = true, que.push(u);
	while (!que.empty()) {
		u = que.front(), que.pop();
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (D[v] > D[u] + 1) {
				D[v] = D[u] + 1;
				if (!vis[v])
					vis[v] = true, que.push(v);
			}
		}
		vis[u] = false;
	}
}
vi nd;
bool bfs(int u) {
	while (!que.empty())
		que.pop();
	nd.clear();
	vis[u] = 0, que.push(u);
	while (!que.empty()) {
		u = que.front(), que.pop();
		nd.pb(u);
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (~vis[v]) {
				if (u != v && vis[u] == vis[v])
					return false;
			} else {
				vis[v] = vis[u] ^ 1;
				que.push(v);
			}
		}
	}
	return true;
}
int s;
vector<pii> E, S;
void dfs(int u, int v) {
	if (dis[u][v] == 1) {
		printf("%d %d\n", u, v);
		swap(col[u], col[v]);
		return;
	}
	rep(i, 1, n + 1)
		if (i != u && i != v && dis[u][i] + dis[i][v] == dis[u][v]) {
			if (col[i] == col[v]) {
				dfs(u, i), dfs(i, v);
			} else {
				dfs(i, v), dfs(u, i);
			}
			break;
		}
}
vi vec[2];
int cnt[2];
void solve() {
	rep(i, 1, n + 1)
		spfa(i, dis[i]);
	rep(i, 1, n + 1)
		vis[i] = -1;
	s = 0, S.clear();
	rep(u, 1, n + 1)
	{
		if (~vis[u])
			continue;
		if (!bfs(u)) {
			puts("-1");
			return;
		}
		int bst = INF;
		rep(C, 0, 2)
		{
			vec[0].clear(), vec[1].clear();
			rep(i, 0, sz(nd))
				if (col[nd[i]] != (vis[nd[i]] ^ C))
					vec[col[nd[i]]].pb(nd[i]);
			if (sz(vec[0]) != sz(vec[1]))
				continue;
			km.init(sz(vec[0]), sz(vec[1]));
			rep(i, 0, sz(vec[0]))
				rep(j, 0, sz(vec[1]))
					km.addEdge(i, j, -dis[vec[0][i]][vec[1][j]]);
			int ret = -km.run();
			if (ret < bst) {
				bst = ret, E.clear();
				rep(i, 0, sz(vec[1]))
					E.pb(mp(vec[0][km.left[i]], vec[1][i]));
			}
		}
		if (bst >= INF) {
			puts("-1");
			return;
		}
		s += bst;
		rep(i, 0, sz(E))
			S.pb(E[i]);
	}
	printf("%d\n", s);
	rep(i, 0, sz(S))
		dfs(S[i].fi, S[i].se);
}
int main() {
//	debug("data");
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		rep(i, 1, n + 1)
			e[i].clear(), col[i] = nxtChar() - '0';
		rep(i, 0, m)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].pb(v), e[v].pb(u);
		}
		solve();
	}
	return 0;
}
