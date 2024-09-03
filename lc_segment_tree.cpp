// vector<int> V为离散的区间端点，包括[询问端点]
vector<int> V;
struct Line {
	int id;
	long double k, b;
	Line() {
		k = b = 0, id = 0;
	}
	Line(long double _k, long double _b) {
		k = _k, b = _b, id = 0;
	}
	long double getf(int x) const {
		return k * x + b;
	}
} nd[N << 2];
struct SegTree {
#define ls ((t)<<1)
#define rs ((t)<<1|1)
	bool less(const Line &p, const Line &q, int x) {
		if (!p.id) return true;
		if (!q.id) return false;
		return p.getf(x) < q.getf(x);		
	}
	void upd(int t, int l, int r, Line line) {
		if (!nd[t].id) nd[t] = line;
		if (less(nd[t], line, V[l])) swap(nd[t], line);	
		if (l == r || nd[t].k == line.k) return ;
		int z = (l + r) >> 1;
		long double ix = (nd[t].b - line.b) / ( -nd[t].k + line.k);	
		if (ix < V[l] || ix > V[r]) return ;	
		if (ix <= V[z]) upd(ls, l, z, nd[t]), nd[t] = line;
		else upd(rs, z + 1, r, line);
	}
	void upd2(int t, int l, int r, int L, int R, Line line) {
		if (L <= l && r <= R) {
			upd(t, l, r, line);
			return ;
		}
		int z = (l + r) >> 1;
		if (L <= z) upd2(ls, l, z, L, R, line);
		if (R > z) upd2(rs, z + 1, r, L, R, line);
	}
	Line qry(int t, int l, int r, int x) {
		if (l == r)
			return nd[t];
		int z = (l + r) >> 1;
		Line ret;
		if (x <= V[z]) ret = qry(ls, l, z, x);
		else ret = qry(rs, z + 1, r, x);
		if (less(ret, nd[t], x)) ret = nd[t];	
		return ret;
	}
} seg;
