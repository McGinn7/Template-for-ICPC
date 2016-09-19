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
const ul BASE = 1e7 + 7;
const int N = 1 << 8;
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
int n, m, ans, re[N], w[N * N], val[N][N][3];
ll f[N * N][N];
char opt[5];
vi e[N * N];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void _max(ll &x, ll y) {
	if (x < y)
		x = y;
}
void dfs(int u, int fa) {
	ll fs = 0;
	int a = (w[u] >> 8), b = (w[u] & (N - 1));
	rep(c, 0, N)
		if (~re[c])
			_max(fs, f[re[c]][b] + (val[c][a][m] << 8));
	inc(ans, (w[u] + fs) * (u + 1) % MOD);
	int tmp = re[a];
	re[a] = u;
	rep(d, 0, N)
		_max(f[u][d], fs + val[d][b][m]);
	rep(i, 0, sz(e[u]))
		if (e[u][i] != fa)
			dfs(e[u][i], u);
	re[a] = tmp;
}
int main() {
	memset(re, -1, sizeof(re));
	rep(i, 0, N)
		rep(j, 0, N)
			val[i][j][0] = (i & j), val[i][j][1] = (i | j), val[i][j][2] = (i
					^ j);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d %s", &n, opt);
		rep(i, 0, n)
		{
			scanf("%d", &w[i]), e[i].clear();
			rep(j, 0, N)
				f[i][j] = 0;
		}
		rep(i, 1, n)
		{
			int f;
			scanf("%d", &f), --f;
			e[f].pb(i);
		}
		switch (opt[0]) {
		case 'A':
			m = 0;
			break;
		case 'O':
			m = 1;
			break;
		case 'X':
			m = 2;
			break;
		}
		ans = 0;
		dfs(0, -1);
		printf("%d\n", ans);
	}
	return 0;
}
