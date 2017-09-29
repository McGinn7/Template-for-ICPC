// set T.L = 0 before use
struct SplayTree {
	bool rev[N];
	int rt, L, fa[N], val[N], siz[N], ch[N][2];
	inline int newnode() {
		++L;	
		siz[L] = 1, fa[L] = rev[L] = ch[L][0] = ch[L][1] = 0;
		return L;
	}
	inline void up(int x) {
		siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]];
	}
	inline void down(int x) {
		if (rev[x]) 
			rev[x] = 0, flip(ch[x][0]), flip(ch[x][1]);
	}
	void flip(int x) {
		rev[x] ^= 1, swap(ch[x][0], ch[x][1]);
	}
	void rot(int x) {
		int y = fa[x];
		down(y), down(x);
		if (rt == y) rt = x;
		int f = ch[y][0] == x;
		ch[y][!f] = ch[x][f];
		if (ch[x][f]) fa[ch[x][f]] = y;
		fa[x] = fa[y];
		if (fa[y]) ch[fa[y]][ch[fa[y]][1] == y] = x;
		ch[x][f] = y;
		fa[y] = x;
		up(y);
	}
	void splay(int x, int g = 0) {
		if (fa[x] == g) down(x);
		else {
			while (fa[x] != g) rot(x);
			up(x);
		}
	}
	int build(int l, int r, int p) {
		if (l > r) return 0;
		int m = (l + r) >> 1;
		int x = newnode();
		val[x] = m - 1, fa[x] = p;
		ch[x][0] = build(l, m - 1, x);
		ch[x][1] = build(m + 1, r, x);
		up(x);
		return x;
	}
	int getk(int k) {
		int x = rt;
		while (x) {
			down(x);
			if (k == siz[ch[x][0]] + 1) 
				break;
			if (k <= siz[ch[x][0]])
				x = ch[x][0];
			else
				k -= siz[ch[x][0]] + 1, 
				x = ch[x][1];
		}
		return x;
	}
} T;

