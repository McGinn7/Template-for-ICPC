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
const ll LINF = 9223372036854775807;
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-7;
//-------------head-------------
struct Gauss {
	static const int N = 305, P = 1e9 + 7;
	int a[N][N];
	int kpow(int a, int b) {
		ll r = 1;
		for (; b; b >>= 1, a = a * a % P)
			if (b & 1)
				r = r * a % P;
		return r;
	}
	int gauss(int n, int m) {
		int i = 0, x = 0;
		for (; i < n && x < m; ++i, ++x) {
			int r = i;
			while (r < n && !a[r][x])
				++r;
			if (r < n) {
				if (r != i)
					rep(j, 0, m + 1)
						swap(a[r][j], a[i][j]);
//				rep(j, 0, n)
//					if (i != j && a[j][x])
//						for (int k = m; k >= x; --k)
//							a[j][k] = (a[j][k]
//									- 1ll * a[i][k] * a[j][x] % P
//											* kpow(a[i][x], P - 2) % P + P) % P;
				rep(j, 0, n)
					if (i != j && a[j][x])
						for (int k = m; k >= x; --k)
							a[j][k] -= a[i][k] * a[j][x] / a[i][x];
			} else {
				--i;
			}
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return n - i;
	}
	void output(int n, int m) {
		rep(i, 0, n)
		{
			rep(j, 0, m)
				printf("%d ", a[i][j]);
			puts("");
		}
	}
} G;
int a[N], b[N];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		int n;
		scanf("%d", &n);
		rep(i, 0, n)
			scanf("%d", &a[i]);
		rep(i, 0, n)
			scanf("%d", &b[i]);
		rep(i, 0, n + 1)
			rep(j, 0, n + 1)
				G.a[i][j] = 0;
		rep(i, 0, n)
			G.a[i][i] = 1;
		int x, y;
		while (~scanf("%d%d", &x, &y)) {
			if (x == 0 && y == 0)
				break;
			G.a[y - 1][x - 1] = 1;
		}
		rep(i, 0, n)
			G.a[i][n] = a[i] ^ b[i];
		int ret = G.gauss(n, n);
		if (~ret) {
			printf("%d\n", 1 << ret);
		} else {
			puts("Oh,it's impossible~!!");
		}
	}
	return 0;
}