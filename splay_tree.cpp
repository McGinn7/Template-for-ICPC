int val[N];
int idx, fa[N], cc[N], sz[N], rev[N], ch[N][2];
int new_node(int v, int _fa=0) {
	int x = ++idx;
	fa[x] = _fa, cc[x] = sz[x] = 1, rev[x] = ch[x][0] = ch[x][1] = 0;

	val[x] = v;
	return x;
}
inline void up(int x) {
	sz[x] = cc[x] + sz[ch[x][0]] + sz[ch[x][1]];
}
inline void upd(int x) {
	if (x) rev[x] ^= 1, swap(ch[x][0], ch[x][1]);
}
inline void down(int x) {
//	if (x && rev[x]) rev[x] = 0, upd(ch[x][0]), upd(ch[x][1]);
}
inline int dir(int x) {
	return x == ch[fa[x]][1];
}
inline void link(int f, int d, int s) {
	if (f) down(f), ch[f][d] = s, up(f);
	if (s) fa[s] = f;
}
void rotate(int x) {
	int y = fa[x], z = fa[fa[x]], dx = dir(x), dy = dir(y);
	link(y, dx, ch[x][!dx]);
	link(x, !dx, y);
	link(z, dy, x);
}
void splay(int &z, int x) {
	for (int f = fa[z]; fa[x] != f; rotate(x))
		if (fa[fa[x]] != f) rotate(dir(x) == dir(fa[x]) ? fa[x] : x);
	z = x;
}
void find_insert(int &z, int v, int d=1) {
	int x = z, y = fa[z];
	while (x && val[x] != v) {
		down(x);
		x = ch[y = x][v > val[x]];
	}
	if (x) {
		cc[x] += d, sz[x] += d;
	} else if (d > 0) {
		x = new_node(v, y);
		link(y, v > val[y], x);
	}
	splay(z, x ? x : y);
}
void loc(int &z, int k) {
	for (int x = z, l = ch[z][0]; k <= sz[x]; l = ch[x][0]) {
		down(x);
		if (k <= sz[l]) {
			x = l;
		} else if (k <= sz[l] + cc[x]) {
			splay(z, x);
			break;
		} else {
			k -= sz[l] + cc[x];
			x = ch[x][1];
		}
	}
}
int merge(int x, int y) {
	if (!x || !y) return x | y;
	loc(y, 1);
	link(y, 0, x);
	return y;
}
void remove(int &z, int v) {
	find_insert(z, v, 0);
	if (!z || val[z] != v) return ;
	--cc[z], --sz[z];
	if (cc[z] <= 0) {
		int l = ch[z][0], r = ch[z][1];
		fa[l] = fa[r] = 0;
		z = merge(l, r);
	}
}
///////////////////////////////////////////////////////
int get_rank(int &z, int v) {
	find_insert(z, v, 0);
	return sz[ch[z][0]] + (val[z] < v ? cc[z] : 0) + 1;
}
int get_kth(int &z, int k) {
	loc(z, k);
	return val[z];
}
int get_prev(int &z, int v) {
	find_insert(z, v, 0);
	if (val[z] < v) return val[z];
	if (!ch[z][0]) return INT_MIN;
	loc(z, sz[ch[z][0]]);
	return val[z];
}
int get_next(int &z, int v) {
	find_insert(z, v, 0);
	if (val[z] > v) return val[z];
	if (!ch[z][1]) return INT_MAX;
	loc(z, sz[ch[z][0]] + cc[z] + 1);
	return val[z];
}
