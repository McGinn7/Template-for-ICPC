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
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, l, x[N][2];
int f[3007][N][2];
vector<int> e[N][2];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int main() {
	scanf("%d%d", &n, &l);
	rep(i, 0, n)
		rep(j, 0, 2) 
			scanf("%d", &x[i][j]);
	rep(i, 0, n)
		rep(j, 0, 2) 
			rep(p, 0, n)
				rep(q, 0, 2) {
					if (i == p)
						continue;
					if (x[p][0] == x[p][1] && q == 1)
						continue;
					if (x[i][j ^ 1] == x[p][q])
						e[i][j].pb(p << 1 | q);
				}
	rep(i, 0, n)
		if (x[i][0] == x[i][1]) {
			if (x[i][0] > l)
				continue;
			f[x[i][0]][i][0] = 1;
		} else {
			rep(j, 0, 2)
				if (x[i][j] <= l)
					f[x[i][j]][i][j] = 1;
		}
	rep(i, 0, l)
		rep(j, 0, n)
			rep(k, 0, 2) {
				if (!f[i][j][k])
					continue;	
				int tmp = f[i][j][k];
				rep(r, 0, sz(e[j][k])) {
					int nj = e[j][k][r] >> 1, nk = e[j][k][r] & 1;
					if (i + x[nj][nk] <= l)
						inc(f[i + x[nj][nk]][nj][nk], tmp);
				}
			}
	int ans = 0;
	rep(i, 0, n)
		rep(j, 0, 2)
			inc(ans, f[l][i][j]);
	printf("%d", ans);
	return 0;
}