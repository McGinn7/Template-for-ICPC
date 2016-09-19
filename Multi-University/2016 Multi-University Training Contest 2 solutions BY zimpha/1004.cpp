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
const int N = 1e5 + 7;
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
int A, B, C = ~(1 << 31), M = (1 << 16) - 1;
int rnd(int last) {
	A = (36969 + (last >> 3)) * (A & M) + (A >> 16);
	B = (18000 + (last >> 3)) * (B & M) + (B >> 16);
	return (C & ((A << 16) + B)) % 1000000000;
}
int n, m, a[N], b[N], c[N], rb[N];
int *p, data[N << 6];
int tag[N << 2], sum[N << 2], *Lrk[N << 2], *Rrk[N << 2];
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

void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int *_alloc(int length) {
	p += length;
	return p - length;
}
#define ls (t << 1)
#define rs ((t << 1) | 1)
void pushUp(int t) {
	sum[t] = sum[ls] + sum[rs];
}
void pushDown(int t) {
	if (tag[t] != -2) {
		tag[ls] = sum[ls] = (~tag[t] ? Lrk[t][tag[t]] : tag[t]), ++sum[ls];
		tag[rs] = sum[rs] = (~tag[t] ? Rrk[t][tag[t]] : tag[t]), ++sum[rs];
	}
	tag[t] = -2;
}
void build(int t, int l, int r) {
	tag[t] = -2, Lrk[t] = _alloc(r - l + 1), Rrk[t] = _alloc(r - l + 1);
	if (l == r) {
		sum[t] = (a[l] >= b[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushUp(t);
	int *vl = b + l, *vr = b + mid + 1;
	int i = 0, j = 0, k = 0, L = mid - l + 1, R = r - mid;
	while (i < L || j < R) {
		while (i < L && (j >= R || vl[i] < vr[j])) {
			Lrk[t][k] = i, Rrk[t][k] = j - 1;
			c[k++] = vl[i++];
		}
		while (j < R && (i >= L || vr[j] <= vl[i])) {
			Lrk[t][k] = i - 1, Rrk[t][k] = j;
			c[k++] = vr[j++];
		}
	}
	memcpy(b + l, c, sizeof(c[0]) * (L + R));
}
void upd(int t, int l, int r, int L, int R, int rk) {
	if (R < l || r < L)
		return;
	if (L <= l && r <= R) {
		tag[t] = rk, sum[t] = rk + 1;
		return;
	}
	pushDown(t);
	int mid = (l + r) >> 1;
	upd(ls, l, mid, L, R, ~rk ? Lrk[t][rk] : rk);
	upd(rs, mid + 1, r, L, R, ~rk ? Rrk[t][rk] : rk);
	pushUp(t);
}
int qry(int t, int l, int r, int L, int R) {
	if (l > r || R < l || r < L)
		return 0;
	if (L <= l && r <= R)
		return sum[t];
	pushDown(t);
	int ret = 0, mid = (l + r) >> 1;
	ret = qry(ls, l, mid, L, R) + qry(rs, mid + 1, r, L, R);
	pushUp(t);
	return ret;
}
int main() {
	int T = io.xuint();
	rep(cas, 0, T)
	{
		n = io.xuint();
		m = io.xuint();
		A = io.xuint();
		B = io.xuint();
		rep(i, 0, n)
			a[i] = io.xuint();
		rep(i, 0, n)
			b[i] = io.xuint();
		rep(i, 0, n)
			rb[i] = b[i];
		sort(rb, rb + n);
		rep(i, 0, n)
			a[i] = upper_bound(rb, rb + n, a[i]) - rb - 1, b[i] = lower_bound(
					rb, rb + n, b[i]) - rb;
		p = data;
		build(1, 0, n - 1);
		int ans = 0, last = 0;
		rep(i, 0, m)
		{
			int l, r, x;
			l = rnd(last) % n;
			r = rnd(last) % n;
			x = rnd(last) + 1;
			if (l > r)
				swap(l, r);
			if ((l + r + x) & 1) {
				x = upper_bound(rb, rb + n, x) - rb - 1;
				upd(1, 0, n - 1, l, r, x);
			} else {
				last = qry(1, 0, n - 1, l, r);
				inc(ans, 1ll * (i + 1) * last % MOD);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
