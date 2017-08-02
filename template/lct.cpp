struct LCT {
	bool rt[N], rev[N];
	int n, fa[N], que[N], ch[N][2];
	// custom information
	int w[N], mx[N], add[N];
	void init(int _n) {
		n = _n;
		rep(i, 0, n) {
			rt[i] = true, rev[i] = false;
			fa[i] = ch[i][0] = ch[i][1] = 0;
		}
	}
	void reverse(int x) {
		rev[x] = !rev[x], swap(ch[x][0], ch[x][1]);
	}
	void updweight(int x, int v) {
		if (x) w[x] += v, mx[x] += v, add[x] += v;
	}
	void up(int x) {
		mx[x] = max(w[x], max(mx[ch[x][0]], mx[ch[x][1]]));
	}
	void down(int x) {
		if (rev[x])
			rev[x] = 0, reverse(ch[x][0]), reverse(ch[x][1]);
		if (add[x])
			updweight(ch[x][0], add[x]), updweight(ch[x][1], add[x]), add[x] = 0;
	}
	void rotate(int x) {
		int y = fa[x], k = (ch[y][0] == x);
		ch[y][!k] = ch[x][k];
		fa[ch[x][k]] = y, fa[x] = fa[y];
		fa[ch[x][k] = y] = x;
		if (rt[y])
			rt[y] = false, rt[x] = true;
		else
			ch[fa[x]][ch[fa[x]][1] == y] = x;
		up(y);
	}
	void update(int x) {
		int top = 0;
		que[top++] = x;
		while (!rt[x]) x = fa[x], que[top++] = x;
		while (top) down(que[--top]);
	}
	void splay(int x) {
		update(x);
		while (!rt[x]) {
			int y = fa[x], z = fa[y];
			if (!rt[y])
				(ch[z][1] == y) == (ch[y][1] == x) ? rotate(y) : rotate(x);
			rotate(x);
		}
		up(x);
	}
	// x->root be a preferred path, like heavy chain
	void access(int x) {
		for (int y = 0; x; y = x, x = fa[x]) {
			splay(x);
			rt[ch[x][1]] = true;
			rt[ch[x][1] = y] = false;
			up(x);
		}
	}
	int getRoot(int x) {
		access(x), splay(x);
		while (ch[x][0]) x = ch[x][0];
		return x;
	}
	// make x be tree root
	void makeRoot(int x) {
		access(x), splay(x), reverse(x);
	}
	// be sure x,y not in one tree
	void addEdge(int x, int y) {
		makeRoot(x), fa[x] = y;
	}
	// delete edge between(x, parent_x)
	void cut(int x) {
		access(x), splay(x);
		if (ch[x][0])
			fa[ch[x][0]] = fa[x], rt[ch[x][0]] = true;
		fa[x] = ch[x][0] = 0;
	}
	void delEdge(int x, int y) {
		// if y is father of x, can remove operation makeRoot(y)
		makeRoot(y), cut(x);
	}
	void delNode(int x) {
		splay(x);	
		rep(i, 0, 2) {
			if (!ch[x][i]) continue;
			fa[ch[x][i]] = fa[x], rt[ch[x][i]] = true;
			fa[x] = ch[x][i] = 0;
		}
	}
} lct;
