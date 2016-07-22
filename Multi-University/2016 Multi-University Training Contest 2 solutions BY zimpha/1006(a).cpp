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
const int N = 2e5 + 7;
const int M = 5e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-9;
ll kpow(ll a, ll b, ll mod) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1)
			ret = ret * a % mod;
	return ret;
}
//--------------head-------------
int n, m, w[N];
vi e[N];
struct BCC {
	vi bcc[N];
	int n, cnt, top, sta[N], dfn[N], low[N];
	void dfs(int u, int dep) {
		int src = 0;
		sta[top++] = u, dfn[u] = low[u] = dep;
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (!dfn[v]) {
				dfs(v, dep + 1);
				low[u] = min(low[u], low[v]);
				if (low[v] >= dfn[u]) {
					while (sta[--top] != v)
						bcc[sta[top]].pb(cnt);
					bcc[u].pb(cnt), bcc[v].pb(cnt++);
				}
			} else if (dfn[v] != dfn[u] - 1 || src++) {
				low[u] = min(low[u], dfn[v]);
			}
		}
	}
	void run(int _n) {
		n = _n;
		cnt = top = 0;
		memset(dfn, 0, sizeof(dfn[0]) * n);
		memset(low, 0, sizeof(low[0]) * n);
		fill_n(bcc, n, vi());
		rep(i, 0, n)
			if (!dfn[i])
				dfs(i, 1);
	}
} G;
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
bool vis[N];
int z[N], mul[N], sub[N], sum[N];
void dfs(int u, int p) {
	vis[u] = true;
	sum[u] = 0, mul[u] = w[u];
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i];
		if (v == p)
			continue;
		dfs(v, u);
		inc(sum[u], mul[v]);
		mul[u] = 1ll * mul[u] * mul[v] % MOD;
	}
}
int W;
void DFS(int u, int p) {
	if (p == -1)
		z[u] = sum[u];
	sub[u] = W;
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i];
		if (v == p)
			continue;
		z[v] = (sum[v] + 1ll * W * kpow(mul[v], MOD - 2, MOD)) % MOD;
		DFS(v, u);
	}
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		rep(i, 0, n)
			scanf("%d", &w[i]), e[i].clear();
		rep(i, 0, m)
		{
			int u, v;
			scanf("%d%d", &u, &v), --u, --v;
			e[u].pb(v), e[v].pb(u);
		}
		G.run(n);
		rep(i, 0, n + G.cnt)
		{
			if (i >= n)
				w[i] = 1;
			e[i].clear(), vis[i] = false;
		}
		rep(u, 0, n)
			rep(i, 0, sz(G.bcc[u]))
			{
				int v = G.bcc[u][i];
				e[u].pb(v + n), e[v + n].pb(u);
			}
		int tot = 0;
		rep(i, 0, n)
			if (!vis[i]) {
				dfs(i, -1);
				inc(tot, W = mul[i]);
				DFS(i, -1);
			}
		int ans = 0;
		rep(i, 0, n)
		{
			inc(z[i], (tot - sub[i] + MOD) % MOD);
			inc(ans, 1ll * (i + 1) * z[i] % MOD);
		}
		printf("%d\n", ans);
	}
	return 0;
}
