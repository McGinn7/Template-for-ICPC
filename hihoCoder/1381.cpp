#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
ll dep[N];
int n, m, cnt, a[N], lft[N], uv[N], w[N], lg[N * 2], son[N], st[N * 2][20];
int tot, p[N], L[N], R[N];
vector<int> e[N], g[N];
void dfs(int u, int fa) {
	p[++tot] = u;
	L[u] = tot;
	lft[u] = cnt;
	st[cnt++][0] = u;
	rep(i, 0, sz(e[u])) {
		int v = uv[e[u][i]] ^ u;
		if (v == fa)
			continue;
		son[e[u][i]] = v;
		dep[v] = dep[u] + w[e[u][i]];
		dfs(v, u);
		st[cnt++][0] = u;
	}
	R[u] = tot;
}
int rmin(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}
void lcaInit() {
	lg[1] = 0;
	rep(i, 2, N * 2)
		lg[i] = lg[i - 1] + (i == (i & -i));
	rep(j, 1, 20) {
		int lim = cnt + 1 - (1 << j);
		rep(i, 0, lim)
			st[i][j] = rmin(st[i][j - 1], st[i + (1 << j >> 1)][j - 1]);
	}
}
int lca(int x, int y) {
	x = lft[x], y = lft[y];
	if (x > y)
		swap(x, y);
	int k = lg[y - x + 1];
	return rmin(st[x][k], st[y + 1 - (1 << k)][k]);
}
#define ls ((t)<<1)
#define rs ((t)<<1|1)
struct Node {
	ll dis;
	int x[2];
} nd[N * 4];
Node merge(const Node &a, const Node &b) {
	Node ret = (a.dis > b.dis ? a : b);
	rep(i, 0, 2)
		rep(j, 0, 2) {
			int _lca = lca(a.x[i], b.x[j]);
//			printf("lca(%d, %d) = %d\n", a.x[i], b.x[j], _lca);
			ll dis = dep[a.x[i]] + dep[b.x[j]] - (dep[_lca] << 1);
			if (ret.dis < dis) {
				ret.dis = dis;
				ret.x[0] = a.x[i], ret.x[1] = b.x[j];
			}
		}
	return ret;
}
void build(int t, int l, int r) {
	if (l == r)	{
		nd[t].x[0] = nd[t].x[1] = p[l], nd[t].dis = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	nd[t] = merge(nd[ls], nd[rs]);
}
Node qry(int t, int l, int r, int L, int R) {
	if (L <= l && r <= R)
		return nd[t];
	int mid = (l + r) >> 1;
	if (R <= mid)
		return qry(ls, l, mid, L, R);
	if (L > mid)
		return qry(rs, mid + 1, r, L, R);
	return merge(qry(ls, l, mid, L, R), qry(rs, mid + 1, r, L, R));
}
bool cmp(const int &x, const int &y) {
	return L[x] < L[y];
}
int solve(int l) {
	for (int i = l + 1; i < cnt; i = solve(i)) 
		if (L[a[i]] <= R[a[l]]) {
			g[a[l]].pb(a[i]);
		} else {
			return i;
		}
	return cnt;
}
int main() {
	scanf("%d", &n);
	rep(i, 1, n) {
		int u, v;
		scanf("%d%d%d", &u, &v, &w[i]);
		--u, --v;
		uv[i] = u ^ v;
		e[u].pb(i), e[v].pb(i);
	}
	cnt = tot = 0, dep[0] = 0;
	dfs(0, -1);	
	lcaInit(), build(1, 1, n);
	scanf("%d", &m);
	rep(_m, 0, m) {
		scanf("%d", &cnt), ++cnt;
		rep(i, 1, cnt) {
			scanf("%d", &a[i]);
			a[i] = son[a[i]];
		}
		sort(a, a + cnt, cmp);
		solve(0);
		Node ret;
		ll ans = 0;
		rep(i, 0, cnt) {
			int u = a[i], l = L[a[i]];
			ret.dis = 0, ret.x[0] = ret.x[1] = u;
			rep(j, 0, sz(g[u])) {
				int v = g[u][j];
				int r = L[v] - 1;
				if (l <= r)
					ret = merge(ret, qry(1, 1, n, l, r));
				l = R[v] + 1;
			}
			g[u].clear();
			if (l <= R[u])
				ret = merge(ret, qry(1, 1, n, l, R[u]));
			ans += ret.dis;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
