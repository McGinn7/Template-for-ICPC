#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<sstream>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, a[N], lg[N], st[N][20];
vector<int> p[N];
vector<pii> ans;
int qry(int l, int r) {
	int k = lg[r - l + 1];
	return min(st[l][k], st[r - (1 << k) + 1][k]);
}
void dfs(int l, int r, int dec) {
	if (l > r)
		return ;
	int i, mn = qry(l, r);
	rep(i, dec, mn)
		ans.pb(mp(l + 1, r + 1));
	if (l == r)
		return ;
	i = lower_bound(p[mn].begin(), p[mn].end(), l) - p[mn].begin();
	int last = l;
	while (i < sz(p[mn]) && p[mn][i] <= r) {
		dfs(last, p[mn][i] - 1, mn);
		last = p[mn][i] + 1;
		++i;
	}
	dfs(last, r, mn);
}
int main() {
	lg[1] = 0;
	rep(i, 2, N)
		lg[i] = lg[i - 1] + (i == (i & -i));
	scanf("%d", &n);
	rep(i, 0, n)
		scanf("%d", a + i), st[i][0] = a[i], p[a[i]].pb(i);
	rep(j, 1, 20)
		for (int i = 0; i + (1 << j) - 1 < n; ++i)
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	dfs(0, n - 1, 0);	
	printf("%d\n", sz(ans));
	rep(i, 0, sz(ans))
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}