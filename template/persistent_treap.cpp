struct Node {
	int ls, rs, siz;
	void clr() {
		ls = rs = 0, siz = 1;
	}
} a[N];
struct Treap {
	int tot;
	void init() {
		tot = 0, srand(time(0));
	}
	inline int _rand() {
		return ((ll) rand() << 14) ^ ((ll) rand());
	}
	inline int newnode() {
		++tot, a[tot].clr();
		return tot;
	}
	void up(int t) {
		a[t].siz = 1 + a[a[t].ls].siz + a[a[t].rs].siz;
	}
	int merge(int t1, int t2) {
		if (!t1 || !t2) {
			if (!t1 && !t2) return 0;
			int nt = newnode();
			a[nt] = a[t1 | t2];
			return nt;
		}
		int nt = newnode();
		if (_rand() % (a[t1].siz + a[t2].siz) < a[t1].siz) {
			a[nt] = a[t1];
			a[nt].rs = merge(a[t1].rs, t2);
		} else {
			a[nt] = a[t2];
			a[nt].ls = merge(t1, a[t2].ls);
		}
		up(nt);
		return nt;
	}
	void split(int t, int k, int &lt, int &rt) {
		if (!t) {
			lt = rt = 0;
			return ;
		}
		int nt = newnode();
		a[nt] = a[t];
		if (a[a[t].ls].siz >= k) {
			rt = nt;
			split(a[t].ls, k, lt, a[nt].ls);
		} else {
			lt = nt;
			split(a[t].rs, k - 1 - a[a[t].ls].siz, a[nt].rs, rt);	
		}
		up(nt);
	}
} T;

