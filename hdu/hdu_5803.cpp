#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<bitset>
#include<vector>
#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const ll LINF = 1e18 + 7;
const int N = 1e4 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
int a[4][70], f[70][16][4][4];
inline void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void read(int x[70]) {
	ll v;
	scanf("%lld", &v);
	rep(i, 0, 63)
		x[i] = (v >> i & 1);
}
inline int calc(int v, int d) {
	int t = 2 * (v - 1) + d;
	if (t < -1)
		return -1;
	return min(3, t + 1);
}
inline int dfs(int t, int st, int d1, int d2) {
	if (d1 < 0 || d2 < 0)
		return 0;
	if (t < 0)
		return d1 > 1 && d2 > 0;
	int &ret = f[t][st][d1][d2];
	if (~ret)
		return ret;
	ret = 0;
	int x[4], v[4];
	rep(i, 0, 4)
		v[i] = (st >> i & 1) ? a[i][t] : 1;
	for (x[0] = 0; x[0] <= v[0]; ++x[0])
	for (x[1] = 0; x[1] <= v[1]; ++x[1])
	for (x[2] = 0; x[2] <= v[2]; ++x[2])
	for (x[3] = 0; x[3] <= v[3]; ++x[3]) {
		int nst = st;
		rep(i, 0, 4)
			if ((st >> i & 1) && x[i] < v[i])
				nst ^= 1 << i;
		inc(ret, dfs(t - 1, nst, 
					calc(d1, (x[0] + x[2]) - (x[1] + x[3])),
					calc(d2, (x[0] + x[3]) - (x[1] + x[2]))));
	}
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		rep(i, 0, 4)
			read(a[i]);		
		memset(f, -1, sizeof(f));
		int ans = dfs(63, 15, 1, 1);
		printf("%d\n", ans);
	}
	return 0;
}
