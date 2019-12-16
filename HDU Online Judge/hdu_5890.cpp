#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 55;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
int n, m, a[N], b[3];
bool ans[N][N][N];
bitset<90> f[N][N][11], g[N][N][11];
void gao(int p, bitset<90> f[N][11], bitset<90> g[N][11]) {
	rep(i, 0, n + 2)
		rep(j, 0, 11)
			f[i][j].reset(), g[i][j].reset();
	f[0][0][0] = 1;
	rep(i, 1, n + 1) {
		rep(j, 0, min(i, 10) + 1)
			f[i][j] = f[i - 1][j];
		if (i != p)	
			rep(j, 1, min(10, i) + 1)
				f[i][j] |= f[i - 1][j - 1] << a[i];
	}
	g[n + 1][0][0] = 1;
	for (int i = n; i >= 1; --i) {
		rep(j, 0, min(n - i + 1, 10) + 1)
			g[i][j] = g[i + 1][j];
		if (i != p)
			rep(j, 1, min(10, n - i + 1) + 1)
				g[i][j] |= g[i + 1][j - 1] << a[i];
	}
}
bitset<90> tmp;
bool solve(int i, int j, int k) {
	rep(r, 0, 11) 
		rep(s, 0, 88) 
			if (f[i][j - 1][r].test(s) && g[k][j + 1][10 - r].test(87 - s))
				return true;
	return false;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);	
		rep(i, 1, n + 1)
			scanf("%d", &a[i]);
		rep(i, 0, n + 1)
			gao(i, f[i], g[i]);
		rep(i, 1, n + 1)
			rep(j, i, n + 1)
				rep(k, j, n + 1)
					ans[i][j][k] = solve(i, j, k);
		scanf("%d", &m);
		rep(i, 0, m) {
			rep(j, 0, 3)
				scanf("%d", &b[j]);
			sort(b, b + 3);		
			puts(ans[b[0]][b[1]][b[2]] ? "Yes" : "No");
		}
	}
	return 0;
}
