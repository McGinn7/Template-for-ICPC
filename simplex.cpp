const double EPS = 1e-8;
const double DINF = 1e15;
struct Simplex {
	int n, m, B[MAXN], N[MAXN];
	db v, ans[MAXN], b[MAXN], c[MAXN], A[MAXN][MAXN];
	/* n - variables, m - equations
	* max f(x) = cx
	* s.t. Ax <= b, x >= 0
	*/
	void init(int _n, int _m) {
		n = _n, m = _m, v = 0;
		rep(i, 1, n + 1) N[i] = i;
		rep(i, 1, m + 1) B[i] = i + n;
	}
	inline int sgn(db x) {
		return (x > EPS) - (x < -EPS);
	}
	void pivot(int l, int e) {
		db tmp = A[l][e];
		b[l] /= tmp, A[l][e] = 1 / tmp;
		rep(i, 1, n + 1) if (i != e) A[l][i] /= tmp;
		rep(i, 1, m + 1) if (i != l) {
			b[i] -= A[i][e] * b[l];
			rep(j, 1, n + 1)
				A[i][j] -= (j != e) * A[i][e] * A[l][j];
			A[i][e] = - A[i][e] / tmp;
		}
		rep(i, 1, n + 1)
			c[i] -= (i != e) * c[e] * A[l][i];
		v += b[l] * c[e];
		c[e] *= -A[l][e];
		swap(B[l], N[e]);
	}
	db run() {
		while (1) {
			int r, l, e = -1;
			db delt = -DINF;
			rep(j, 1, n + 1) if (sgn(c[j]) > 0) {
				db tmp = DINF;
				rep(i, 1, m + 1) 
					if (sgn(A[i][j]) > 0 && b[i] / A[i][j] < tmp)
						r = i, tmp = b[i] / A[i][j];
				if (delt < tmp * c[j])
					l = r, e = j, delt = tmp * c[j];
			}
			if (e == -1) break;
			pivot(l, e);
		}
		rep(i, 1, n + 1) rep(j, 1, m + 1)
			if (B[j] == i) {
				ans[i] = (j <= m ? b[j] : 0);
				break;
			}
		return v;
	}
} sp;

