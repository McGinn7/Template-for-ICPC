#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) begin(x),end(x)
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << "=" << x << ", "
#define de(x) cout << #x << "=" << x << endl
//-------

const int MAX_ROW = 500 + 2;
const int MAX_COLUMN = 900 + 2;
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

int ans;

class ExactCover : public DLX {
private:
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
	
	int timestamp[MAX_COLUMN];	
	int AStar() {
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
	bool dfs(int step = 0) {
		if (step + AStar() >= ans) return false;
		if (0 == R[0]) {
			ans = step;
			return true;
		}
		int c = R[0];
		iter(j, 0, R) if (csum[j] < csum[c])	
			c = j;
		remove(c);
		iter(i, c, D) {
			iter(j, i, R) remove(col[j]);
			dfs(step + 1);
			iter(j, i, L) resume(col[j]);
		}
		resume(c);
		return false;
	}
} ec;

int main() {
	int T; scanf("%d", &T);
	rep(cas, 0, T) {
		int n, m, p; scanf("%d %d %d", &n, &m, &p);
		ec.init(p, n * m);	
		rep(r, 0, p) {
			int x1, y1, x2, y2;	
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			rep(i, x1, x2) rep(j, y1, y2) 
				ec.set(r, i * m + j + 1);
		}
		ans = INT_MAX;
		ec.dfs();
		ans = ans == INT_MAX ? -1 : ans;
		printf("%d\n", ans);
	}
	return 0;
}

