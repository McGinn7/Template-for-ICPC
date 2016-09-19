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
const int N = 15;
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
int n, m;
ll c[N][N], dp[N][N], bin[N * N];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void init() {
	bin[0] = 1;
	rep(i, 1, N * N)
		bin[i] = (bin[i - 1] * 3) % MOD;
	rep(i, 0, N)
	{
		c[i][0] = c[i][i] = 1;
		rep(j, 1, i)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
	}
}
int solve(int n, int m) {
	if (~dp[n][m])
		return dp[n][m];
	int ret = bin[n * m];
	rep(i, 1, n + 1)
		rep(j, 0, m + 1)
		{
			if (i == n && j == m)
				continue;
			inc(ret,
					MOD
							- 1ll * c[n - 1][i - 1] * c[m][j] % MOD
									* bin[(n - i) * (m - j)] % MOD * solve(i, j)
									% MOD);
		}
	return dp[n][m] = ret;
}
int main() {
	init();
	memset(dp, -1, sizeof(dp));
	while (~scanf("%d%d", &n, &m)) {
		printf("%d\n", solve(n, m));
	}
	return 0;
}
