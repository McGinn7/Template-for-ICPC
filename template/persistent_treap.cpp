struct Node {
	int ls, rs, siz;
	void clr() {
		ls = rs = 0, siz = 1;
	}
} a[N], b[M];
struct Treap {
	int tot, id[N], que[M];
	void init() {
		tot = 0, srand(time(NULL));
	}
	inline int _rand() {
		return (((ll) rand() << 14) ^ ((ll) rand()));
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
	void rebuild(int &root) {
		if (root == 0) return ;
		memset(id, -1, sizeof(id));
		int h = 0, t = 0;
		++t, que[t] = root, id[root] = t, b[t] = a[root];
		while (h < t) {
			int u = que[++h];
			if (a[u].ls) {
				if (id[a[u].ls] == -1) {
					id[a[u].ls] = ++t;
					que[t] = a[u].ls, b[t] = a[a[u].ls];
				}
				b[h].ls = id[a[u].ls];
			}
			if (a[u].rs) {
				if (id[a[u].rs] == -1) {
					id[a[u].rs] = ++t;
					que[t] = a[u].rs, b[t] = a[a[u].rs];
				}
				b[h].rs = id[a[u].rs];
			}
		}
		tot = t;
		rep(i, 1, tot + 1) a[i] = b[i];
		root = id[root];
	}
} T;
