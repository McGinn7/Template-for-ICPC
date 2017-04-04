struct Mat {
	int a[2][2];
	void init(int x) {
		rep(i, 0, 2)
			rep(j, 0, 2)
				a[i][j] = (i == j ? x : 0);
	}
	Mat operator*(const Mat &p) {
		Mat ret;
		ret.init(0);
		rep(i, 0, 2)
			rep(j, 0, 2)
				rep(k, 0, 2)
					inc(ret.a[i][j], 1ll * a[i][k] * p.a[k][j] % mod);
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
} A;
