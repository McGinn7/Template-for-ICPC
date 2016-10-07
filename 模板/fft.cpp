/*
* 支持取模
*/
struct C {
	double r, i;
	C() {
		r = i = 0;
	}
	C(double _r, double _i) {
		r = _r, i = _i;
	}
	C operator+(const C &p) const {
		return C(r + p.r, i + p.i);
	}
	C operator-(const C &p) const {
		return C(r - p.r, i - p.i);
	}
	C operator*(const C &p) const {
		return C(r * p.r - i * p.i, r * p.i + i * p.r);
	}
};
inline C conj(const C &p) {
	return C(p.r, -p.i);
}
C w[N];
int L, bitrev[N];
void init(int len) { // len = n + m
	L = 0;
	while (1 << L <= len)
		++L;
	int n = 1 << L;
	rep(i, 0, n)
		bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	rep(i, 0, n)
		w[i] = C(cos(2 * Pi * i / n), sin(2 * Pi * i / n));
}
void fft(C a[], const int &n) {
	rep(i, 0, n)
		if (i < bitrev[i])
			swap(a[i], a[bitrev[i]]);
	for (int i = 2, d = n >> 1; i <= n; i <<= 1, d >>= 1)
		for (int j = 0; j < n; j += i) {
			C *l = a + j, *r = a + j + (i >> 1), *p = w;
			for (int k = 0; k < (i >> 1); ++k) {
				C tmp = (*r) * (*p);
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += d;
			}
		}
}
int n, m, p;
C A[N], B[N];
C dfa[N], dfb[N], dfc[N], dfd[N];
vector<int> gao(const vector<int> &a, const vector<int> &b, ll pw) {
	int n = 1 << L;
	rep(i, 0, n)
		A[i] = B[i] = C(0, 0);
	rep(i, 0, m)
		A[i * pw % m] = C(a[i] & 32767, a[i] >> 15);
	rep(i, 0, m)
		B[i] = C(b[i] & 32767, b[i] >> 15);
	fft(A, n), fft(B, n);
	rep(i, 0, n)
	{
		int j = (n - i) & (n - 1);
		static C da, db, dc, dd;
		da = (A[i] + conj(A[j])) * C(0.5, 0);
		db = (A[i] - conj(A[j])) * C(0, -0.5);
		dc = (B[i] + conj(B[j])) * C(0.5, 0);
		dd = (B[i] - conj(B[j])) * C(0, -0.5);
		dfa[j] = da * dc, dfb[j] = da * dd;
		dfc[j] = db * dc, dfd[j] = db * dd;
	}
	rep(i, 0, n)
	{
		A[i] = dfa[i] + dfb[i] * C(0, 1);
		B[i] = dfc[i] + dfd[i] * C(0, 1);
	}
	fft(A, n), fft(B, n);
	vector<int> ret(m, 0);
	rep(i, 0, n)
	{
		ll da = (ll) (A[i].r / n + 0.5) % MOD;
		ll db = (ll) (A[i].i / n + 0.5) % MOD;
		ll dc = (ll) (B[i].r / n + 0.5) % MOD;
		ll dd = (ll) (B[i].i / n + 0.5) % MOD;
		inc(ret[i % m], (da + ((db + dc) << 15) + (dd << 30)) % MOD);
	}
	return ret;
}
//----------原始版本-------------

struct C {
	double r, i;
	C() {
		r = i = 0;
	}
	C(double _r, double _i) {
		r = _r, i = _i;
	}
	C operator+(const C &p) const {
		return C(r + p.r, i + p.i);
	}
	C operator-(const C &p) const {
		return C(r - p.r, i - p.i);
	}
	C operator*(const C &p) const {
		return C(r * p.r - i * p.i, r * p.i + i * p.r);
	}
};
void fft(C x[], int n, int rev) {
	int i, j, k, t;
	for (i = 1; i < n; ++i) {
		for (j = 0, k = n >> 1, t = i; k; k >>= 1, t >>= 1)
			j = j << 1 | (t & 1);
		if (i < j)
			swap(x[i], x[j]);
	}
	int s, ds;
	for (s = 2, ds = 1; s <= n; ds = s, s <<= 1) {
		C w = C(1, 0), t;
		C wn = C(cos(2.0 * rev * Pi / s), sin(2.0 * rev * Pi / s));
		for (k = 0; k < ds; ++k, w = w * wn)
			for (i = k; i < n; i += s) {
				t = w * x[i + ds];
				x[i + ds] = x[i] - t;
				x[i] = x[i] + t;
			}
	}
	if (rev == -1)
		for (i = 0; i < n; ++i)
			x[i].r /= n;
}
