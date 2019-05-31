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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const double MODI = acos(-1.0);
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
int n, a[N], f[N], g[N], t[N];
void init() {
	f[0] = 1;
	rep(i, 1, N)
		f[i] = 1ll * f[i - 1] * i % MOD;
	g[N - 1] = kpow(f[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; --i)
		g[i] = 1ll * g[i + 1] * (i + 1) % MOD;
	t[0] = 1;
	rep(i, 1, N)
		t[i] = (t[i - 1] * 2) % MOD;
}
void change(int *x, int len) {
	int i, j, k;
	for (i = 1, j = len >> 1; i < len - 1; ++i) {
		if (i < j)
			swap(x[i], x[j]);
		k = len >> 1;
		while (j >= k)
			j -= k, k >>= 1;
		if (j < k)
			j += k;
	}
}
const int G = 3;
void ntt(int *x, int len, int rev) {
	change(x, len);
	int id = 0;
	for (int h = 2; h <= len; h <<= 1) {
		++id;
		int wn = kpow(G, (MOD - 1) / (1 << id));
		for (int j = 0; j < len; j += h) {
			int w = 1;
			for (int k = j; k < j + h / 2; ++k) {
				int u = x[k] % MOD, t = 1ll * w * x[k + h / 2] % MOD;
				x[k] = (u + t) % MOD;
				x[k + h / 2] = ((u - t) % MOD + MOD) % MOD;
				w = 1ll * w * wn % MOD;
			}
		}
	}
	if (rev == -1) {
		for (int i = 1; i < len / 2; ++i)
			swap(x[i], x[len - i]);
		int inv = kpow(len, MOD - 2);
		for (int i = 0; i < len; ++i)
			x[i] = 1ll * x[i] * inv % MOD;
	}
}
int A[N * 4], B[N * 4];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int main() {
	init();
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		rep(i, 1, n + 1)
			scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		int len = 1;
		while (len < (n + 1) * 2)
			len <<= 1;
		memset(A, 0, sizeof(A[0]) * len);
		memset(B, 0, sizeof(B[0]) * len);
		rep(i, 1, n + 1)
			A[i] = 1ll * f[n - i] * t[i - 1] % MOD * a[i] % MOD;
		rep(i, 0, n + 1)
			B[i] = g[i];
		ntt(A, len, 1), ntt(B, len, 1);
		rep(i, 0, len)
			A[i] = 1ll * A[i] * B[i] % MOD;
		ntt(A, len, -1);
		int sum = 0;
		for (int nk = n; nk > 0; --nk) {
			inc(sum, 1ll * A[nk] * g[n - nk] % MOD);
			printf("%d ", sum);
		}
		puts("");
	}
	return 0;
}