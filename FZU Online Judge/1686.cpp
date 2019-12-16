#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
#include<climits>
#include<iostream>
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

const int MAX_ROW = 15 * 15;
const int MAX_COLUMN = 15 * 15 + 1;
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

class SetCover : public DLX {
private:
	void remove(const int &c) {
		iter(i, c, D) DLX::remove(i, L, R);
	}

	void resume(const int &c) {
		iter(i, c, U) DLX::resume(i, L, R);
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
	bool dfs(int step = 0) {
		if (step + astar() >= ans) return false;
		if (0 == R[0]) {
			ans = min(ans, step);
			return true;
		}
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

int a[15][15];

int main() {
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) { 
		int id = 0;
		rep(i, 0, n) rep(j, 0, m) {
			scanf("%d", &a[i][j]);
			id += a[i][j];
			if (a[i][j] > 0)
				a[i][j] = id;
		}
	
		int r, c; scanf("%d %d", &r, &c);
		sc.init((n - r + 1) * (m - c + 1), id);		
		rep(i, 0, n - r + 1)
			rep(j, 0, m - c + 1) {
				int row = i * (m - c + 1) + j;	
				rep(x, 0, r) rep(y, 0, c) {
					if (!a[i + x][j + y])
						continue;
					sc.set(row, a[i + x][j + y]);
				}
			}
		ans = INT_MAX;
		sc.dfs();
		printf("%d\n", ans);
	}
	return 0;
}

