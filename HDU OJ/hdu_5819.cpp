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
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
ll kpow(ll a, ll b) {
	ll r = 1;
	while (b > 0) {
		if (b & 1)
			r = r * a % MOD;
		a = a * a % MOD, b >>= 1;
	}
	return r;
}
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int n, a[N], f[N][N], s[N][N];
int main() {
//	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		rep(i, 1, n + 1)
			scanf("%d", &a[i]);
		f[0][0] = 1;
		a[1] = 1, a[n] = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] == 1) {
				for (int j = 1; j <= i; ++j)
					f[i][j] = f[i - 1][j - 1];
			} else {
				for (int j = 1; j <= i; ++j)
					f[i][j] = s[i - 1][j];
				inc(f[i][1], s[i - 1][1]);
			}
			s[i][i + 1] = 0;
			for (int j = i; j > 0; --j) {
//				printf("f[%d][%d] = %d\n", i, j, f[i][j]);
				s[i][j] = f[i][j];
				inc(s[i][j], s[i][j + 1]);
			}
		}
		int ans = 1ll * s[n - 1][1] * kpow(kpow(2, n - 1), MOD - 2) % MOD;
		printf("Case #%d: %d\n", cas + 1, ans);
	}
	return 0;
}