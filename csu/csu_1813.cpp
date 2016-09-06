#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = 1e16 + 7;
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, m, f[N][N], up[N][N], down[N][N];
char a[N][N], b[N][N];
pii sta[N];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void push(int &top, int &sum, pii &p) {
	while (top > 0 && sta[top].first >= p.first) {
		p.second += sta[top].second, sum -= sta[top].first * sta[top].second;
		--top;
	}
	sum += p.first * p.second, sta[++top] = p;
}
pii solve(char a[][N], int n, int m) {
//	rep(i, 1, n + 1)
//	{
//		rep(j, 1, m + 1)
//			putchar(a[i][j]);
//		puts("");
//	}
	rep(j, 1, m + 1)
		down[n + 1][j] = 0;
	rep(i, 1, n + 1)
	{
		rep(j, 1, m + 1)
			if (a[i][j] == '0') {
				up[i][j] = 1 + up[i - 1][j];
			} else {
				up[i][j] = 0;
			}
		int sum = 0, top = 0;
		rep(j, 1, m + 1)
		{
			pii p = mp(up[i][j], 1);
			push(top, sum, p);
//			printf("f[%d][%d] = %d\n", i, j, sum);
			f[i][j] = sum;
			inc(f[i][j], f[i - 1][j]), inc(f[i][j], f[i][j - 1]), inc(f[i][j],
					MOD - f[i - 1][j - 1]);
		}
	}
	int c[2] = { 0, 0 };
	for (int i = n; i >= 1; --i) {
		for (int j = m; j >= 1; --j)
			if (a[i][j] == '0') {
				down[i][j] = 1 + down[i + 1][j];
			} else {
				down[i][j] = 0;
			}
		int sum = 0, top = 0;
		for (int j = m; j >= 1; --j)
			if (a[i][j] == '0') {
				pii p = mp(down[i][j], 1);
				push(top, sum, p);
				inc(c[0], 1ll * sum * f[i - 1][j - 1] % MOD);
				inc(c[1], 1ll * sum * f[n][j - 1] % MOD);
			} else {
				sum = top = 0;
			}
	}
	return mp(c[0], c[1]);
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		rep(i, 1, n + 1)
		{
			gets(a[i] + 1);
			while (!strlen(a[i] + 1))
				gets(a[i] + 1);
			rep(j, 1, m + 1)
				b[j][n - i + 1] = a[i][j];
		}
		pii ret[2];
		ret[0] = solve(a, n, m);
//		printf("ret[%d] = (%d, %d)\n", 0, ret[0].first, ret[0].second);
		ret[1] = solve(b, m, n);
//		printf("ret[%d] = (%d, %d)\n", 1, ret[1].first, ret[1].second);
		int ans = 0;
		rep(i, 0, 2)
			inc(ans, MOD - ret[i].first), inc(ans, ret[i].second);
		printf("%d\n", ans);
	}
	return 0;
}
