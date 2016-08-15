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
