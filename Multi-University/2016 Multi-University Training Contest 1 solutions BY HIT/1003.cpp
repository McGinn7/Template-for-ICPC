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
const int N = 1e3 + 7;
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
int n, m, c[N], G[N];
ll C[N], CC[N];
char a[N][N], b[N][N];
ll calc(int n, int m, char a[][N]) {
	rep(j, 0, m)
	{
		c[j] = n;
		rep(i, 0, n)
			if (a[i][j] == 'G') {
				--c[j];
				break;
			}
	}
	C[0] = c[0], CC[0] = 0;
	rep(j, 1, m)
		C[j] = C[j - 1] + c[j], CC[j] = CC[j - 1] + j * c[j];
	ll ret = 0;
	rep(i, 0, m)
		ret += c[i] * ((CC[m - 1] - CC[i]) - i * (C[m - 1] - C[i]));
	return ret << 1;
}
ll calc2(int n, int m, char a[][N]) {
	ll ret = 0;
	rep(j, 0, m)
	{
		G[j] = -1;
		rep(i, 0, n)
			if (a[i][j] == 'G') {
				G[j] = i;
				break;
			}
	}
	rep(j, 0, m)
		if (~G[j]) {
			ll tot = n - 1 - G[j];
			for (int J = j - 1, L = G[j]; J >= 0; --J)
				if (~G[J] && G[J] > L) {
					tot += n - 1 - G[J];
					L = G[J];
				} else
					break;
			for (int J = j + 1, L = G[j]; J < m; ++J)
				if (~G[J] && G[J] > L) {
					tot += n - 1 - G[J];
					L = G[J];
				} else
					break;
			ret += tot * G[j] * 4ll;
		}
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		rep(i, 0, n)
			scanf(" %s", a[i]);
		rep(i, 0, n)
			rep(j, 0, m)
				b[j][i] = a[i][j];
		ll ans = 0;
		ans += calc(n, m, a) + calc(m, n, b);
		ans += calc2(n, m, a) + calc2(m, n, b);
		printf("%.4lf\n", 1.0 * ans / (C[m - 1] * C[m - 1]));
	}
	return 0;
}
/*
 3
 2 2
 ##
 G#
 2 2
 ##
 ##
 3 3
 ###
 #G#
 ###
 */
