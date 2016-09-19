#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<assert.h>
#include<sstream>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e18 + 7;
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
struct Gauss {
	const static int N = 2e2 + 7;
	int a[N][N];
	int solve(int n, int m) {
		int i = 0, c = 0;
		for (; i < n && c < m; ++i, ++c) {
			int r = i;
			while (r < n && !a[r][c])
				++r;
			if (r >= n) {
				--i;
				continue;
			}
			if (r != i)
				rep(j, 0, m + 1)
					swap(a[r][j], a[i][j]);
			rep(j, 0, n)
				if (i != j && a[j][c])
					for (int k = m; k >= c; --k)
						a[j][k] ^= a[i][k];
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return m - i;
	}
} G;
int n, a[N], ans[N];
vector<int> e[N];
bool solve() {
	rep(i, 0, n)
		rep(j, 0, n + 1)
			G.a[i][j] = 0;
	rep(i, 0, n)
	{
//		G.a[i][i] = 1;
		G.a[i][n] = a[i];
		rep(j, 0, sz(e[i]))
			G.a[i][e[i][j]] = 1;
	}
	if (G.solve(n, n) == -1)
		return false;
	return true;
}
int main() {
	scanf("%d", &n);
	rep(i, 0, n)
	{
		int k;
		scanf("%d", &k);
		rep(_k, 0, k)
		{
			int x;
			scanf("%d", &x), --x;
			e[x].pb(i);
		}
	}
	rep(i, 0, n)
		scanf("%d", &a[i]);
	int L = -1;
	rep(t, 0, 2)
	{
		if (solve()) {
			L = 0;
			rep(i, 0, n)
				rep(j, 0, n)
					if (G.a[i][n] && G.a[i][j]) {
						ans[L++] = j + 1;
						break;
					}
			break;
		}
		rep(i, 0, n)
			a[i] ^= 1;
	}
	printf("%d\n", L);
	if (~L) {
		sort(ans, ans + L);
		rep(i, 0, L)
			printf("%d ", ans[i]);
	}
	return 0;
}