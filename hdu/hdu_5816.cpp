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
const int N = 22;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, m, hp, b[N];
ll cnt[1 << 20], g[N], a[N], c[N][N], f[N][N][N];
void init() {
	a[0] = 1;
	rep(i, 1, N)
		a[i] = a[i - 1] * i;
	memset(c, 0, sizeof(c));
	rep(i, 0, N)
	{
		c[i][0] = c[i][i] = 1;
		rep(j, 1, i)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	cnt[0] = 0;
	rep(i, 1, 1 << 20)
		cnt[i] = cnt[i ^ (i & -i)] + 1;
}
void dfs(int t, int st, int dmg) {
	if (t >= m) {
		g[cnt[st]] += (dmg >= hp);
		return;
	}
	dfs(t + 1, st, dmg);
	dfs(t + 1, st | 1 << t, dmg + b[t]);
}
int main() {
	init();
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d%d", &hp, &n, &m);
		rep(i, 0, m)
			scanf("%d", &b[i]);
		memset(g, 0, sizeof(g));
		dfs(0, 0, 0);
		memset(f, 0, sizeof(f));
		f[1][0][1] = 1, f[1][1][0] = 1;
		for (int i = 1; i < n + m; ++i)
			for (int j = 1; j <= i && j <= n; ++j) {
				for (int k = 0; k <= m && k + j <= i; ++k)
					if (f[i][j][k]) {
						ll tmp = f[i][j][k];
						if (i <= n + m - 2) {
							if (k + 2 <= m)
								f[i + 2][j - 1][k + 2] += tmp;
							if (k + 1 <= m && i - k + 1 <= n)
								f[i + 2][j][k + 1] += tmp * 2;
							if (i - k + 2 <= n)
								f[i + 2][j + 1][k] += tmp;
						} else {
							if (k + 1 <= m)
								f[i + 1][j - 1][k + 1] += tmp;
							if (i - k + 1 <= n)
								f[i + 1][j][k] += tmp;
						}
					}
			}
		ll P = 0, Q = c[n + m][n] * a[m];
		for (int i = 1; i <= n + m; ++i) {
			for (int k = 1; k <= i && k <= m; ++k) {
				if (f[i][0][k])
					P += f[i][0][k] * g[k] * a[k] * c[n + m - i][m - k]
							* a[m - k];
				if (i == n + m)
					for (int j = 1; j <= n; ++j)
						if (f[i][j][k])
							P += f[i][j][k] * g[k] * a[k] * c[n + m - i][m - k]
									* a[m - k];
			}
		}
		ll _g = __gcd(P, Q);
		P /= _g, Q /= _g;
		printf("%lld/%lld\n", P, Q);
	}
	return 0;
}