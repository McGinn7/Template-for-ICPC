#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
//-------------head-------------
int n, K, L, R, a[N], par[N], f[N][55];
vector<int> V, e[N], w[N];
void _max(int &x, int y) {
	if (x < y)
		x = y;
}
void dfs(int u, int p, const int &MID) {
	par[u] = p, f[u][0] = 0;
	rep(i, 1, R + 1)
		f[u][i] = -INF;
	rep(i, 0, sz(e[u]))
	{
		int v = e[u][i];
		if (v == p)
			continue;
		dfs(v, u, MID);
		rep(j, 0, R)
			_max(f[u][j + 1], f[v][j] + (w[u][i] <= MID ? K - 1 : -1));
	}
}
int mxf[55], que[55];
bool check(const int &MID) {
	dfs(0, -1, MID);
	rep(i, 0, n)
		rep(j, L, R + 1)
			if (f[i][j] > 0)
				return true;
	rep(u, 0, n)
	{
		rep(i, 0, R + 1)
			mxf[i] = -INF;
		rep(i, 0, sz(e[u]))
		{
			int v = e[u][i];
			if (v == par[u])
				continue;
			int y = 1, qh = 0, qt = 0;
			for (int x = R - 1; x >= 0; --x) {
				while (x + y + 1 <= R) {
					while (qh < qt && mxf[que[qt - 1]] <= mxf[y])
						--qt;
					que[qt++] = y++;
				}
				while (qh < qt && que[qh] + x + 1 < L)
					++qh;
				if (qh < qt
						&& mxf[que[qh]] + f[v][x]
								+ (w[u][i] <= MID ? K - 1 : -1) > 0)
					return true;
			}
			rep(j, 0, R)
				_max(mxf[j + 1], f[v][j] + (w[u][i] <= MID ? K - 1 : -1));
		}
	}
	return false;
}
int solve() {
	int l = *min_element(V.begin(), V.end()), r = *max_element(V.begin(),
			V.end());
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		check(mid) ? r = mid : l = mid;
	}
	if (check(l))
		return l;
	if (check(r))
		return r;
	return -1;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		V.clear();
		rep(i, 0, n)
			e[i].clear(), w[i].clear();
		rep(i, 1, n)
		{
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c), --u, --v;
			V.pb(c);
			e[u].pb(v), w[u].pb(c);
			e[v].pb(u), w[v].pb(c);
		}
		scanf("%d%d%d", &K, &L, &R);
		printf("%d\n", solve());
	}
	return 0;
}