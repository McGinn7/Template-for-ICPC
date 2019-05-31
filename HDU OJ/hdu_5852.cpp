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
const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1000000007;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
struct FastIO {
	static const int S = 1310720;
	int wpos;
	char wbuf[S];
	FastIO() :
			wpos(0) {
	}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len)
			return -1;
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x;
	}
	inline int xint() {
		int s = 1, c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		if (c == '-')
			s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char *s) {
		int c = xchar();
		while (c <= 32)
			c = xchar();
		for (; c > 32; c = xchar())
			*s++ = c;
		*s = 0;
	}
	inline void wchar(int x) {
		if (wpos == S)
			fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(int x) {
		if (x < 0)
			wchar('-'), x = -x;
		char s[24];
		int n = 0;
		while (x || !n)
			s[n++] = '0' + x % 10, x /= 10;
		while (n--)
			wchar(s[n]);
	}
	inline void wstring(const char *s) {
		while (*s)
			wchar(*s++);
	}
	~FastIO() {
		if (wpos)
			fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;
int n, m, a[107], b[107], fac[N], gfn[N];
ll kpow(ll a, ll b) {
	ll r = 1;
	while (b > 0) {
		if (b & 1)
			r = r * a % MOD;
		a = a * a % MOD, b >>= 1;
	}
	return r;
}
void init() {
	fac[0] = gfn[0] = 1;
	rep(i, 1, N)
	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		gfn[i] = kpow(fac[i], MOD - 2);
	}
}
int C(int n, int m) {
	if (m < 0 || n < m)
		return 0;
	return 1ll * fac[n] * gfn[m] % MOD * gfn[n - m] % MOD;
}
struct Gauss {
	const static int N = 107;
	int a[N][N];
	int solve(int n, int m) {
		int i = 0, c = 0, R = 1;
		for (; i < n && c < m; ++i, ++c) {
			int r = i;
			while (r < n && !a[r][c])
				++r;
			if (r >= n)
				return 0;
			if (r != i) {
				R = MOD - R;
				rep(j, 0, m)
					swap(a[r][j], a[i][j]);
			}
			R = 1ll * R * a[i][i] % MOD;
			rep(j, i + 1, n)
				if (a[j][c]) {
					ll tmp = 1ll * a[j][c] * kpow(a[i][c], MOD - 2) % MOD;
					for (int k = m - 1; k >= c; --k)
						a[j][k] = (a[j][k] - 1ll * a[i][k] * tmp % MOD + MOD)
								% MOD;
				}
		}
		return R;
	}
} G;
int main() {
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
	init();
	int T;
//	scanf("%d", &T);
	T = io.xuint();
	rep(cas, 0, T)
	{
//		scanf("%d%d", &n, &m);
		n = io.xuint();
		m = io.xuint();
		rep(i, 0, m)
//			scanf("%d", &a[i]);
			a[i] = io.xuint();
		rep(i, 0, m)
//			scanf("%d", &b[i]);
			b[i] = io.xuint();
		rep(i, 0, m)
			rep(j, 0, m)
				G.a[i][j] = C((b[j] - a[i]) + (n - 1), n - 1);
		printf("%d\n", G.solve(m, m));
	}
	return 0;
}