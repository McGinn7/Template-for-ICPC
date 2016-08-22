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
int kpow(int a, int b) {
	int r = 1;
	for (; b; b >>= 1, a = a * a % 7)
		if (b & 1)
			r = r * a % 7;
	return r;
}
struct Gauss {
	const static int N = 2e2 + 7, P = 7;
	int a[N][N];
	void inc(int &x, int y) {
		x += y;
		if (x >= P)
			x -= P;
	}
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
						inc(a[j][k],
								P
										- 1ll * a[i][k] * a[j][c]
												* kpow(a[i][c], P - 2) % P);
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return m - i;
	}
} G;
int n, m;
char st[10], ed[10];
int trans(char str[]) {
	if (str[0] == 'M')
		return 0;
	if (str[2] == 'E')
		return 1;
	if (str[0] == 'W')
		return 2;
	if (str[1] == 'H')
		return 3;
	if (str[0] == 'F')
		return 4;
	if (str[1] == 'A')
		return 5;
	return 6;
}
int main() {
	while (~scanf("%d%d", &n, &m) && (n + m)) {
		rep(i, 0, m)
			rep(j, 0, n + 1)
				G.a[i][j] = 0;
		rep(i, 0, m)
		{
			int k, d;
			scanf("%d %s %s", &k, st, ed);
			d = (trans(ed) - trans(st) + 1 + 7) % 7;
			G.a[i][n] = d;
			rep(_k, 0, k)
			{
				int x;
				scanf("%d", &x), --x;
				++G.a[i][x];
				if (G.a[i][x] >= 7)
					G.a[i][x] = 0;
			}
		}
		int ret = G.solve(m, n);
		if (ret == 0) {
			rep(i, 0, n)
			{
				int x = G.a[i][n] * kpow(G.a[i][i], 5) % 7;
				if (i)
					putchar(' ');
				if (x < 3)
					x += 7;
				printf("%d", x);
			}
			puts("");
		} else {
			puts(~ret ? "Multiple solutions." : "Inconsistent data.");
		}
	}
	return 0;
}