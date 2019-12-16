#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<bitset>
#include<vector>
#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 2e4 + 7;
const int P = 1e8 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
ll mod;
struct Mat {
	ll a[3][3];
	void inc(ll &x, ll y) {
		x += y;
		if (x >= mod)
			x -= mod;
	}
	void init(int x) {
		rep(i, 0, 3)
			rep(j, 0, 3)
				a[i][j] = (i == j ? x : 0);
	}
	Mat operator*(Mat &p) {
		Mat ret;
		ret.init(0);
		rep(i, 0, 3)
			rep(j, 0, 3)
				rep(k, 0, 3)
					inc(ret.a[i][j], a[i][k] * p.a[k][j] % mod);
		return ret;
	}
	Mat operator^(ll b) {
		Mat ret, a = *this;
		ret.init(1);
		while (b > 0) {
			if (b & 1)
				ret = ret * a;
			a = a * a, b >>= 1;
		}
		return ret;
	}
	void out() {
		cout << "Mat.mod = " << mod << endl;
		rep(i, 0, 3) {
			rep(j, 0, 3)
				printf("%lld ", a[i][j]);
			puts("");
		}
	}
} G;
ll g[20];
int n, y, x, s;
bool vis[N];
vector<int> pri;
void init() {
	memset(vis, false, sizeof(vis));
	rep(i, 2, N) {
		if (!vis[i])
			pri.pb(i);
		rep(j, 0, sz(pri)) {
			if (i * pri[j] > N)
				break;
			vis[i * pri[j]] = true;
		}
	}
	g[0] = 0, g[1] = 1;
	rep(i, 2, 20)
		g[i] = 6ll * g[i - 1] - g[i - 2] + ((i & 1) ? 1 : -1);
}
int phi(int n) {
	int ret = n;
	rep(i, 0, sz(pri)) {
		if (pri[i] > n)
			break;
		if (n % pri[i] == 0) {
			ret = ret / pri[i] * (pri[i] - 1);
			while (n % pri[i] == 0)
				n /= pri[i];
		}
	}
	if (n > 1)
		ret = ret / n * (n - 1);
	return ret;
}
ll calc(ll n) {
	if (n <= 12)
		return g[n];	
	mod = phi(s + 1);
	G.a[0][0] = 6, G.a[0][1] =  mod - 1, G.a[0][2] = 1;
	G.a[1][0] = 1, G.a[1][1] =  0, G.a[1][2] = 0;
	G.a[2][0] = 0, G.a[2][1] =  0, G.a[2][2] = mod - 1;
	G = G ^ (n - 1);	
	ll ret = G.a[0][0] - G.a[0][2];
	if (ret < 0)
		ret += mod;
	ret += mod;
	return ret;
}
ll kpow(ll a, ll b, ll mod) {
	ll r = 1;
	while (b > 0) {
		if (b & 1)
			r = r * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return r;
}
int main() {
	init();
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d%d%d", &n, &y, &x, &s);
		ll ans = kpow(x, calc(1ll * n * y), s + 1);
//		printf("%lld\n", ans);
		printf("%I64d\n", ans);		
	}
	return 0;
}
