/*
    1. Initialize two values L and H to 0/1 and 1/0, respectively.
    2. Until q is found, repeat the following steps:
        Let L = a/b and H = c/d; compute the mediant M = (a + c)/(b + d).
        If M is less than q, then q is in the open interval (M,H); 
			replace L by M and continue.
        If M is greater than q, then q is in the open interval (L,M); 
			replace H by M and continue.
        In the remaining case, q = M; terminate the search algorithm.
*/
namespace SBT {
	const int INF = 1e9 + 7;
	typedef __int128 T;
	typedef pair<T, T> V; // V = [double|long double|fraction]
	inline int cmp(const V &a, const V &b) {
		T x = a.fi * b.se - a.se * b.fi;
		return (x > 0) - (x < 0);
	}
	inline bool in(const V &a, const V &b, const V &c) {
		return 0 <= cmp(c, a) && cmp(c, b) < 0;
	}
	pii operator+(const pii &a, const pii &b) {
		return mp(a.fi + b.fi, a.se + b.se);
	}
	pii operator*(const pii &a, int x) {
		return mp(a.fi * x, a.se * x);
	}
	void search(V v, int MAXB, pii &lo, pii &hi, int f) {
		V x;
		int l = 0, r = f > 0 ? (hi.se ? (MAXB - lo.se) / hi.se : INF) : 
			(lo.se ? (MAXB - hi.se) / lo.se : INF);
		while (l + 1 < r) {
			int z = (l + r) >> 1;
			x = f > 0 ? lo + hi * z : lo * z + hi;
			f * cmp(x, v) <= 0 ? l = z : r = z;
		}
		x = f > 0 ? lo + hi * r : lo * r + hi;
		r = f * cmp(x, v) <= 0 ? r : l;
		f > 0 ? lo = lo + hi * r : hi = lo * r + hi;
	}
	pii solve(V v, int MAXB) { // find ROUND_HALF_UP(a / b) = v, b <= MAXB
		V L = mp(v.fi * 10 - 5, v.se * 10);	
		V R = mp(v.fi * 10 + 5, v.se * 10);
		pii lo(0, 1), hi(1, 0);
		while (true) {
			V m = mp(lo.fi + hi.fi, lo.se + hi.se);	
			if (in(L, R, m)) return mp(m.fi, m.se);
			search(v, MAXB, lo, hi, 1);
			search(v, MAXB, lo, hi, -1);
			if (in(L, R, lo)) return lo;
			if (in(L, R, hi)) return hi;
		}
		return mp(-1, -1);
	}
};
