#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e2 + 7;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int n, m, e, t[N];
vector<int> p[N];
vector<pii> ans;
void solve(int x) {
	vector<int> nd;
	nd.pb(x);
	int y = t[x];
	while (y != -1 && y != x) {
		nd.pb(y);
		y = t[y];
	}
	if (y == -1) {
		for (int i = sz(nd) - 2; i >= 0; --i)
			ans.pb(mp(nd[i], nd[i + 1]));
		t[nd.front()] = -1;
		rep(i, 1, sz(nd))
			t[nd[i]] = nd[i];
	} else {
		rep(i, 1, n + 1)
			if (t[i] == -1) {
				e = i;
				break;
			}
		ans.pb(mp(nd.back(), e));
		for (int i = sz(nd) - 2; i >= 0; --i)
			ans.pb(mp(nd[i], nd[i + 1]));
		ans.pb(mp(e, nd.front()));
		rep(i, 0, sz(nd))
			t[nd[i]] = nd[i];
	}
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m + 1)
	{
		int ni;
		scanf("%d", &ni);
		rep(j, 0, ni)
		{
			int x;
			scanf("%d", &x);
			p[i].pb(x);
		}
	}
	memset(t, -1, sizeof(t));
	int S = 0;
	rep(i, 1, m + 1)
		rep(j, 0, sz(p[i]))
			t[p[i][j]] = ++S;
	rep(i, 1, n + 1)
		if (~t[i] && t[i] != i)
			solve(i);
	printf("%d\n", sz(ans));
	rep(i, 0, sz(ans))
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}