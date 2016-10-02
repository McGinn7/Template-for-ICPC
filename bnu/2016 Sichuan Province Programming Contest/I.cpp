#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e15 + 7;
const int N = 1007;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
//----------head-----------
int n, a[10], b[10], p[10], f[10];
ll g[10], dp[10][N], sum[10][N];
vector<int> r[10];
void solve() {
	int rk = 0;
	rep(i, 1, 6)
		if (sz(r[i]) > 0)
			rk = i;
	rep(i, 1, rk + 1)
		if (!sz(r[i]))
			return;
	int cnt = 1;
	rep(i, 0, n)
	{
		f[i] = 1;
		rep(j, 0, i)
			if (p[j] < p[i])
				f[i] = max(f[i], f[j] + 1);
		cnt = max(cnt, f[i]);
	}
//	rep(i, 0, n)
//		printf("%d ", p[i]);
//	puts("");
//	printf("cnt = %d\n", cnt);
	dp[0][0] = 1, sum[0][0] = 1;
	rep(i, 1, N)
		sum[0][i] = 1;
	rep(i, 1, rk + 1)
	{
		int L = -INF, R = INF;
		rep(j, 0, sz(r[i]))
			L = max(L, a[r[i][j]]), R = min(R, b[r[i][j]]);
//		printf("L = %d, R = %d\n", L, R);
		rep(j, 0, N)
			dp[i][j] = 0;
		rep(j, L, R + 1)
			dp[i][j] = sum[i - 1][j - 1];
		rep(j, 1, N)
			sum[i][j] = sum[i][j - 1] + dp[i][j];
	}
//	printf("sum = %lld\n", sum[rk][N - 1]);
	g[cnt] += sum[rk][N - 1];
}
void dfs(int t) {
	if (t >= n) {
		solve();
		return;
	}
	rep(i, 1, n + 1)
	{
		r[i].pb(t), p[t] = i;
		dfs(t + 1);
		r[i].pop_back();
	}
}
int main() {
	scanf("%d", &n);
	rep(i, 0, n)
		scanf("%d%d", a + i, b + i);
	memset(g, 0, sizeof(g));
	dfs(0);
	rep(i, 1, n + 1)
	{
		if (i - 1)
			putchar(' ');
		printf("%lld", g[i]);
	}
	return 0;
}