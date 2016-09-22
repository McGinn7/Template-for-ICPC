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
const int K = 16;
const int N = (1 << K) + 7;
const int INF = 1e9 + 7;
const int MOD = 1004535809;
//-------------head------------
template <typename T>
void inc(T &x, T y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int f[N], rf[N];
ll dp[N], buf[N], rig[K][N];
ll kpow(ll a, ll b, ll mod) {
	ll r = 1;
	while (b > 0) {
		if (b & 1)
			r = r * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return r;
}
namespace NTT {
	const int ort = 3;
	void ntt(ll A[], int n, int inv) {
		// inv == 1 ? ntt : intt;
		ll w = 1, d = kpow(ort, (MOD - 1) / n, MOD), t;
		int i, j, c, s;
		if (inv == -1) {
			for (i = 1, j = n - 1; i < j; ++i, --j)
				swap(A[i], A[j]);
			for (t = kpow(n, MOD - 2, MOD), i = 0; i < n; ++i)
				A[i] = A[i] * t % MOD;
		}
		for (s = n >> 1; s; s >>= w = 1, d = d * d  % MOD)
			for (c = 0; c < s; ++c, w = w * d % MOD)
				for (i = c; i < n; i += s << 1) {
					A[i | s] = (A[i] + MOD - (t = A[i | s])) * w % MOD;
					A[i] = (A[i] + t) % MOD;
				}
		for (i = 1; i < n; ++i) {
			for (j = 0, s = i, c = n >> 1; c; c >>= 1, s >>= 1)
				j = j << 1 | (s & 1);
			if (i < j)
				swap(A[i], A[j]);
		}
	}
}
void init() {
	f[0] = rf[0] = 1;
	rep(i, 1, N)
		f[i] = 1ll * i * f[i - 1] % MOD;
	rf[N - 1] = kpow(f[N - 1], MOD - 2, MOD);
	for (int i = N - 2; i > 0; --i)
		rf[i] = 1ll * (i + 1) * rf[i + 1] % MOD;
	rep(k, 1, K) {
		memset(rig[k], 0, sizeof(rig[k][0]) << k);
		rep(i, 1, 1 << k)
			rig[k][i] = (i < 2 ? 1ll : kpow(i, i - 2, MOD)) * rf[i - 1] % MOD;
		NTT::ntt(rig[k], 1 << k, 1);
	}
}
void solve(int l, int k) {
	if (k == 0) {
		if (l > 0)
			dp[l] = dp[l] * rf[l] % MOD * f[l - 1] % MOD;
		return ;
	}
	int m = l + (1 << (k - 1));
	solve(l, k - 1);
	memset(buf, 0, sizeof(buf[0]) << k);
	rep(i, 0, m - l) 
		buf[i] = dp[l + i];
	NTT::ntt(buf, 1 << k, 1);
	rep(i, 0, 1 << k)
		buf[i] = buf[i] * rig[k][i]	% MOD;
	NTT::ntt(buf, 1 << k, -1);
	rep(i, 1 << (k - 1), 1 << k) 
		inc(dp[l + i], buf[i]);
	solve(m, k - 1);
}
int main() {
	init();
	dp[0] = 1;
	solve(0, K);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		int n, ans;
		scanf("%d", &n);	
		ans = kpow(2, 1ll * n * (n - 1) / 2, MOD);
		inc(ans, MOD - (int) (1ll * dp[n] * f[n] % MOD));
		printf("%d\n", ans);
	}
	return 0;
}
