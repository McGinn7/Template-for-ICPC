/**
 * @note initialize idx = 0 before use
 * @verified_by hdu1890(Robotic Sort) 
 */
struct SplayTree {
	/**
	 * Fixed variables
	 * @rev lazy tag denoting reverse subtree
	 * @rt root of splay tree
	 * @idx number of nodes created
	 * @fa node's parent
	 * @ch node's children
	 * @size subtree size 
	 */
	bool rev[N];	
	int rt, idx, fa[N], ch[N][2], size[N];
	SplayTree() { idx = 0; }	
	int newNode() {
		size[++idx] = 1;
		rev[idx] = false;
		fa[idx] = ch[idx][0] = ch[idx][1] = 0;		
		return idx;	
	}
	inline void flip(int x) {
		rev[x] ^= 1, swap(ch[x][0], ch[x][1]);
	}
	inline void up(int x) {
		size[x] = 1 + size[ch[x][0]] + size[ch[x][1]];
	}
	inline void down(int x) {
		if (!rev[x]) return;
		rev[x] = false, flip(ch[x][0]), flip(ch[x][1]);
	}
	/* rotate node x according to whether x is 
	 * left or right child of its parent node. */
	void rot(int x) {
		int y = fa[x], k = ch[y][0] == x;
		down(y);
		down(x);
		ch[y][!k] = ch[x][k];
		fa[ch[x][k]] = y, fa[x] = fa[y];
		fa[ch[x][k] = y] = x;
		if (rt == y) rt = x;
		else ch[fa[x]][ch[fa[x]][1] == y] = x;
		up(y);			
	}
	void splay(int x, int f) {
		while (fa[x] != f) {
			int y = fa[x], z = fa[fa[x]];
			if (z != f) 
				rot((ch[z][1] == y) == (ch[y][1] == x) ? y : x);
			rot(x);	
		}
		up(x);
	}	
};
