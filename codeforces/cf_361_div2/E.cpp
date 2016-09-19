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
const ul BASE = 33;
const int N = 4e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-8;
ll kpow(ll a, ll b) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a % MOD)
		if (b & 1)
			ret = ret * a % MOD;
	return ret;
}
//--------------head--------------
int n, k, l[N], r[N], f[N], g[N], c[N];
vi d;
ll C(int n, int m) {
	if (n < m)
		return 0;
	return 1ll * f[n] * g[m] % MOD * g[n - m] % MOD;
}
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int main() {
	f[0] = 1, g[0] = 1;
	rep(i, 1, N)
		f[i] = 1ll * f[i - 1] * i % MOD, g[i] = kpow(f[i], MOD - 2);
	scanf("%d%d", &n, &k);
	rep(i, 0, n)
		scanf("%d%d", &l[i], &r[i]), d.pb(l[i]), d.pb(r[i]);
	sort(all(d));
	d.erase(unique(all(d)), d.end());
	rep(i, 0, n)
		l[i] = lower_bound(all(d), l[i]) - d.begin(), r[i] = lower_bound(all(d),
				r[i]) - d.begin();
	int ans = 0, cnt = 0;
	rep(i, 0, n)
		++c[l[i]], --c[r[i] + 1];
	rep(i, 0, sz(d)) {
		cnt += c[i], c[i] = 0;
		inc(ans, C(cnt, k));
	}
	rep(i, 0, n)
		++c[l[i]], --c[r[i]];
	cnt = 0;
	rep(i, 0, sz(d) - 1) {
		cnt += c[i];
		inc(ans, C(cnt, k) * (d[i + 1] - d[i] - 1) % MOD);
	}
	printf("%d", ans);
	return 0;
}
