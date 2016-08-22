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
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-7;
//-------------head-------------
int n = 20, a[N], fr[N];
struct Gauss {
	static const int N = 107;
	int a[N][N];
	int solve(int n, int m) {
		int i = 0, c = 0, t = 0;
		for (; i < n && c < m; ++i, ++c) {
			int r = i;
			while (r < n && !a[r][c])
				++r;
			if (r < n) {
				if (r != i)
					rep(j, 0, m + 1)
						swap(a[r][j], a[i][j]);
				rep(j, 0, n)
					if (i != j && a[j][c])
						for (int k = m; k >= c; --k)
							a[j][k] ^= a[i][k];
			} else {
				fr[t++] = c, --i;
			}
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return m - i;
	}
} G;
int x[N];
int solve() {
	int t = G.solve(n, n), ans = INF;
	rep(mask, 0, 1 << t)
	{
		int cnt = 0;
		rep(i, 0, t)
		{
			x[fr[i]] = (mask >> i & 1);
			cnt += x[fr[i]];
		}
		rep(i, 0, n - t)
		{
			int st = G.a[i][n];
			rep(j, n - t, n)
				st ^= (x[j] & G.a[i][j]);
			cnt += st;
		}
		ans = min(ans, cnt);
	}
	return ans;
}
int main() {
	rep(i, 0, n)
		scanf("%d", &a[i]);
	rep(i, 0, n)
	{
		G.a[i][n] = a[i];
		G.a[i][i] = 1;
		if (i)
			G.a[i][i - 1] = 1;
		if (i + 1 < n)
			G.a[i][i + 1] = 1;
	}
	printf("%d\n", solve());
	return 0;
}