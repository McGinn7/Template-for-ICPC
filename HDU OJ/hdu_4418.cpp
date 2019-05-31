#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<assert.h>
#include<sstream>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e18 + 7;
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
struct Gauss {
	const static int N = 207;
	double a[N][N];
	void solve(int n, int m) {
		int r, c;
		for (r = c = 0; r < n && c < m; ++r, ++c) {
			int mxr = r;
			rep(i, r + 1, n)
				if (fabs(a[i][c]) > fabs(a[mxr][c]))
					mxr = i;
			if (fabs(a[mxr][c]) < EPS) {
				--r;
				continue;
			}
			if (mxr != r)
				swap(a[r], a[mxr]);
			rep(i, 0, n)
				if (i != r && fabs(a[i][c]) > EPS)
					for (int j = m; j >= c; --j)
						a[i][j] -= a[r][j] * a[i][c] / a[r][c];
		}
	}
} G;
int n, m, x, y, d, cnt, L, a[N], p[N], id[N];
bool vis[N];
queue<int> que;
bool bfs() {
	cnt = 0;
	while (!que.empty())
		que.pop();
	memset(vis, false, sizeof(vis[0]) * (L + 1));
	id[x] = cnt++, vis[x] = true, que.push(x);
	while (!que.empty()) {
		int s = que.front();
		que.pop();
		rep(i, 1, m + 1)
			if (p[i]) {
				int t = (s + i) % L;
				if (!vis[t])
					id[t] = cnt++, vis[t] = true, que.push(t);
			}
	}
	return vis[y] || vis[L - y];
}
void solve() {
	if (x == y) {
		printf("%.2lf\n", 0.0);
		return;
	}
	if (!bfs()) {
		puts("Impossible !");
		return;
	}
	rep(i, 0, cnt)
		rep(j, 0, cnt + 1)
			G.a[i][j] = 0;
	rep(s, 0, L)
		if (vis[s]) {
			G.a[id[s]][id[s]] = 1;
			if (s != y && s != L - y)
				rep(i, 1, m + 1)
					if (p[i]) {
						int t = (s + i) % L;
						if (vis[t])
							G.a[id[s]][id[t]] -= p[i] / 100.0, G.a[id[s]][cnt] +=
									i * p[i] / 100.0;
					}
		}
	G.solve(cnt, cnt);
	double ans = G.a[0][cnt] / G.a[0][0];
	printf("%.2lf\n", ans + EPS);
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d%d%d%d", &n, &m, &y, &x, &d);
		rep(i, 1, m + 1)
			scanf("%d", &p[i]);
		if (d == 1)
			x = n - 1 - x, y = n - 1 - y;
		L = 2 * n - 2;
		rep(i, 0, n)
			a[i] = i;
		rep(i, n, L)
			a[i] = L - i;
		solve();
	}
	return 0;
}