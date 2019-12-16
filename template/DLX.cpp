const int MAX_ROW = 81 * 9;
const int MAX_COLUMN = 81 * 4 + 1;
const int MAXN = MAX_ROW * MAX_COLUMN;

class DLX {
protected:
	#define iter(i,s,nxt) for(int i=nxt[s];i!=s;i=nxt[i])  
	
	int nodes;
	int L[MAXN], R[MAXN], U[MAXN], D[MAXN];
	int row[MAXN], col[MAXN];
	int rhead[MAX_ROW], csum[MAX_COLUMN];

	inline void link(int a, int b, int *prv, int *nxt) {
		nxt[a] = b, prv[b] = a;		
	}

	inline void insert(int a, int b, int *prv, int *nxt) {
		int c = nxt[a];
		link(a, b, prv, nxt);	
		link(b, c, prv, nxt);
	}

	inline void remove(int x, int *prv, int *nxt) {
		nxt[prv[x]] = nxt[x];
		prv[nxt[x]] = prv[x];
	}

	inline void resume(int x, int *prv, int *nxt) {
		nxt[prv[x]] = x;
		prv[nxt[x]] = x;
	}

	int timestamp[MAX_COLUMN];
	int astar() {
		++timestamp[0];
		int h = 0;
		iter(c, 0, R) if (timestamp[c] != timestamp[0]) {
			++h;
			iter(i, c, D) iter(j, i, R)
				timestamp[col[j]] = timestamp[0];
		}
		return h;
	}

public:
	// [0, rows) × [0, columns]
	void init(int rows, int columns) {
		fill(rhead, rhead + rows, -1);
		rep(j, 0, columns + 1) {
			csum[j] = 0;
			link(j, j + 1, L, R);
			link(j, j, U, D);
		}
		R[nodes = columns] = 0;	
	}
	// set the bit at (i, j) to 1 
	void set(int i, int j) {
		int x = ++nodes;
		++csum[j], insert(j, x, U, D);
		if (rhead[i] < 0)
			rhead[i] = L[x] = R[x] = x;
		else
			insert(rhead[i], x, L, R);
		row[x] = i, col[x] = j;
	}
};

class ExactCover : public DLX {
private:
	// remove row i if the bit at (i, c) is 1
	void remove(const int &c) {
		DLX::remove(c, L, R);
		iter(i, c, D) iter(j, i, R) 
			--csum[col[j]], DLX::remove(j, U, D);
	}

	void resume(const int &c) {
		DLX::resume(c, L, R);
		iter(i, c, U) iter(j, i, L)
			++csum[col[j]], DLX::resume(j, U, D);
	}

public:
	bool dfs(int step = 0) {
		if (0 == R[0]) return true;
		int c = R[0];
		iter(j, 0, R) if (csum[j] < csum[c])	
			c = j;
		remove(c);
		iter(i, c, D) {
			iter(j, i, R) remove(col[j]);
			if (dfs(step + 1)) return true;
			iter(j, i, L) resume(col[j]);
		}
		resume(c);
		return false;
	}
} ec;

class SetCover : public DLX {
private:
	// remove column c
	void remove(const int &c) {
		iter(i, c, D) DLX::remove(i, L, R);
	}

	void resume(const int &c) {
		iter(i, c, U) DLX::resume(i, L, R);
	}

public:
	bool dfs(int step = 0) {
		if (0 == R[0]) return true;
		int c = R[0];
		iter(j, 0, R) if (csum[j] < csum[c])
			c = j;
		iter(i, c, D) {
			remove(i);
			iter(j, i, R) remove(j);
			dfs(step + 1);
			iter(j, i, L) resume(j);
			resume(i);
		}
		return false;
	}
} sc;
