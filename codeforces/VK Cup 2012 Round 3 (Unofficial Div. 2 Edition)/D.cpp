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
int n, m, f[N], st[N];
bool vis[N];
vector<int> e[N], g[N];
queue<int> que;
void bfs(int c, const vector<int> e[]) {
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		st[u] |= c;
		if (c != 1 && f[u] == 1)
			continue;
		rep(i, 0, sz(e[u])) {
			int v = e[u][i];
			if (!vis[v])
				vis[v] = true, que.push(v);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n + 1)
		scanf("%d", f + i), vis[i] = false;
	rep(i, 0, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].pb(v), g[v].pb(u);
	}
	memset(vis, false, sizeof(vis[0]) * (n + 1));
	rep(i, 1, n + 1)
		if (f[i] == 1)
			vis[i] = true, que.push(i);
	bfs(1, e);
	memset(vis, false, sizeof(vis[0]) * (n + 1));
	rep(i, 1, n + 1)
		if (f[i] == 2)
			vis[i] = true, que.push(i);
	bfs(2, g);
	rep(i, 1, n + 1)
		printf("%d\n", st[i] == 3);

	return 0;
}