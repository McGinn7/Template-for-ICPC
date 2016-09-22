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
const int MOD = 1004535809;
//-------------head------------
int n, m, a[20], ansx;
ll ansd, cnt[22][22];
void dfs(int t, int x, ll diff) {
	if (t >= m) {
		if (diff < ansd || (diff == ansd && x < ansx))
			ansx = x, ansd = diff;
		return ;
	}
	for (a[t] = 0; a[t] < 2; ++a[t]) {
		ll nd = diff + cnt[t][t];
		rep(i, 0, t)
			if (a[i] ^ a[t])
				nd -= cnt[t][i];
			else
				nd += cnt[t][i];
		dfs(t + 1, x | (a[t] << t), nd);
	}
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		memset(cnt, 0, sizeof(cnt));
		int pre, now;
		scanf("%d", &pre);
		rep(i, 1, n) {
			scanf("%d", &now);
			if (pre != now) {
				int mx, mn, hig = 20;
				while (!((pre ^ now) >> hig & 1))
					--hig;
				mx = max(pre, now), mn = min(pre, now);
				for (int j = hig; j >= 0; --j)
					cnt[hig][j] += (mx >> j & 1) - (mn >> j & 1);
			}
			pre = now;
		}
		m = 20;
		while (m >= 0 && !cnt[m - 1][m - 1])
			--m;
		rep(i, 0, 20)
			rep(j, 0, i + 1)
				cnt[i][j] <<= j;
		ansd = LINF;
		dfs(0, 0, 0);	
		printf("%d %lld\n", ansx, ansd);
	}
	return 0;
}
