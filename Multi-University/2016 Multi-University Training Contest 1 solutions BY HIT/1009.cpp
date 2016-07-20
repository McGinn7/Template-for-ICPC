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
const int N = 1e7 + 7;
const int P = 1e3 + 7;
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
int a[17], b[17], ans[17][17], g[17][17], f[2][1 << 16];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void F(int m) {
	int t = 0;
	fill(f[t], f[t] + (1 << m), 0);
	f[t][(1 << m) - 1] = 1;
	rep(i, 1, 17)
	{
		rep(j, 0, m)
		{
			t ^= 1;
			fill(f[t], f[t] + (1 << m), 0);
			rep(mask, 0, 1 << m)
			{
				inc(f[t][mask ^ (1 << j)], f[t ^ 1][mask]);
				if (j && ((mask >> (j - 1) & 3) == 2))
					inc(f[t][mask | 3 << (j - 1)], f[t ^ 1][mask]);
			}
		}
		g[i][m] = f[t][(1 << m) - 1];
	}
}
void S(int m) {
	rep(mask, 0, 1 << (m - 1))
	{
		int st = mask | (1 << (m - 1));
		rep(i, 1, 17)
		{
			a[i] = 1;
			int last = -1;
			rep(j, 0, m)
				if (st >> j & 1) {
					a[i] = 1ll * a[i] * g[i][j - last] % MOD;
					last = j;
				}
		}
		rep(i, 1, 17)
		{
			b[i] = a[i];
			rep(j, 1, i)
				inc(b[i], MOD - 1ll * b[j] * a[i - j] % MOD);
			if (__builtin_popcount(mask) & 1) {
				inc(ans[i][m], MOD - b[i]);
			} else {
				inc(ans[i][m], b[i]);
			}
		}
	}
}
int main() {
	rep(m, 1, 17)
		F(m);
	rep(m, 1, 17)
		S(m);
	int n, m;
	while (~scanf("%d%d", &n, &m))
		printf("%d\n", ans[n][m]);
	return 0;
}
