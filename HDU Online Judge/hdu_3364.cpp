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
const int N = 55;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
struct Gauss {
	const static int N = 55;
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
int n, m, a[N][N], state[N];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		memset(a, 0, sizeof(a));
		rep(i, 0, m)
		{
			int k;
			scanf("%d", &k);
			rep(_k, 0, k)
			{
				int x;
				scanf("%d", &x), --x;
				a[x][i] = 1;
			}
		}
		printf("Case %d:\n", cas + 1);
		int Q;
		scanf("%d", &Q);
		rep(_Q, 0, Q)
		{
			rep(i, 0, n)
				scanf("%d", &state[i]);
			rep(i, 0, n)
			{
				rep(j, 0, m)
					G.a[i][j] = a[i][j];
				G.a[i][m] = state[i];
			}
			int ret = G.solve(n, m);
			if (ret == -1) {
				puts("0");
			} else {
				printf("%I64d\n", 1ll << ret);
			}
		}
	}
	return 0;
}