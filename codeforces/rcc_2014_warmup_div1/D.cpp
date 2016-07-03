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
const int N = 1e5 + 7;
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
int n, m, fa[N], lg[N], rt[N], dep[N], f[N][20], g[N][20];
vi e[N];
queue<int> que;
int bfs(int u, int root) {
	int ret = u;
	fa[u] = rt[u] = root, dep[u] = 0;
	que.push(u);
	while (!que.empty()) {
		u = que.front(), que.pop();
		if (dep[u] > dep[ret])
			ret = u;
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (v == fa[u])
				continue;
			fa[v] = u, rt[v] = root, dep[v] = dep[u] + 1;
			que.push(v);
		}
	}
	return ret;
}
void MAX(int &x, int y) {
	if (x < y)
		x = y;
}
int qry(int st[][20], int l, int r) {
	if (l > r)
		return 0;
	int k = lg[r - l + 1];
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
	lg[1] = 0;
	rep(i, 2, N)
		lg[i] = lg[i - 1] + (i == (i & -i));
	scanf("%d", &n);
	rep(i, 1, n)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].pb(v), e[v].pb(u);
	}
	int A = bfs(1, 0), B = bfs(A, 0);
	for (int i = B, p = 0; i; p = i, i = fa[i]) {
		int far = 0;
		rt[i] = i;
		rep(j, 0, sz(e[i]))
			if (e[i][j] != p && e[i][j] != fa[i])
				far = max(far, dep[bfs(e[i][j], i)] + 1);
		f[dep[i]][0] = far + dep[i];
		g[dep[i]][0] = far + dep[B] - dep[i];
	}
	for (int j = 1; (1 << j) <= dep[B] + 1; ++j)
		for (int i = 0; i + (1 << j) - 1 <= dep[B]; ++i) {
			f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
			g[i][j] = max(g[i][j - 1], g[i + (1 << j - 1)][j - 1]);
		}
	scanf("%d", &m);
	while (m--) {
		int x, y, dx = 0, dy = 0, mid, ans = 0;
		scanf("%d%d", &x, &y);
		if (dep[rt[x]] > dep[rt[y]])
			swap(x, y);
		if (x != rt[x])
			dx = 1 + dep[x], x = rt[x];
		if (y != rt[y])
			dy = 1 + dep[y], y = rt[y];
		mid = (dep[x] - dx + dep[y] + dy) >> 1;
		MAX(ans,
				max(min(dx, dy + dep[y] - dep[x]) + dep[x],
						min(dy, dx + dep[y] - dep[x]) + dep[B] - dep[y]));
		MAX(ans,
				max(qry(f, dep[x], min(mid, dep[y])) - dep[x] + dx,
						qry(g, max(dep[x], dep[x] - dx + dep[y] + dy - mid),
								dep[y]) - dep[B] + dep[y] + dy));
		printf("%d\n", ans);
	}
	return 0;
}
