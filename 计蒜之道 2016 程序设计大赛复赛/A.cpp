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
#define sqr(x) ((x)*(x))
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
const int N = 3e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 2e9 + 7;
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
int n;
ll ans, g[N][N], d[20][N][N];
void cpy(ll a[][N], ll b[][N]) {
	rep(i, 0, n)
		rep(j, 0, n)
			a[i][j] = b[i][j];
}
void floyd(int l, int r, ll f[][N]) {
	rep(k, l, r + 1)
		rep(i, 0, n)
			rep(j, 0, n)
				if (~f[i][k] && ~f[k][j]
						&& (f[i][j] == -1 || f[i][j] > f[i][k] + f[k][j]))
					f[i][j] = f[i][k] + f[k][j];
}
void dfs(int l, int r, int dep) {
	if (l == r) {
		rep(i, 0, n)
			rep(j, 0, n)
				if (i != j && i != l && j != l)
					ans += d[dep][i][j];
		return;
	}
	int mid = (l + r) >> 1;
	// left
	cpy(d[dep + 1], d[dep]);
	floyd(l, mid, d[dep + 1]);
	dfs(mid + 1, r, dep + 1);
	// right
	cpy(d[dep + 1], d[dep]);
	floyd(mid + 1, r, d[dep + 1]);
	dfs(l, mid, dep + 1);
}
int main() {
	scanf("%d", &n);
	rep(i, 0, n)
		rep(j, 0, n)
			scanf("%lld", &g[i][j]);
	cpy(d[0], g);
	dfs(0, n - 1, 0);
	printf("%lld", ans);
	return 0;
}
