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
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, l, k, a[N], p[N];
double f[2][N][N << 1];
double solve() {
	int t = 0;
	double pro;
	f[0][0][min(n << 1, n + k)] = 1.0;
	rep(i, 0, n) {
		t ^= 1, pro = p[i + 1] / 100.0;
		memset(f[t], 0, sizeof(f[t]));
		rep(j, 0, i + 1)
			rep(k, 0, 1 + (n << 1)) {
//				printf("f[%d][%d][%d] = %lf\n", i, j, k, f[t ^ 1][j][k]);
				// lose	
				f[t][j][k] += (1.0 - pro) * f[t ^ 1][j][k];
				// win
				if (k + a[i + 1] >= 0)
					f[t][j + 1][min(n << 1, k + a[i + 1])] += pro * f[t ^ 1][j][k];
			}
	}
	double ans = 0.0;
	rep(j, l, n + 1)
		rep(k, n, (n << 1) + 1)
			ans += f[t][j][k];
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &l, &k);
	rep(i, 1, n + 1)
		scanf("%d", p + i);
	rep(i, 1, n + 1)
		scanf("%d", a + i);
	printf("%.10lf\n", solve());
	return 0;
}