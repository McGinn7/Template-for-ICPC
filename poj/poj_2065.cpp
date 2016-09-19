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
int n, P;
char F[N];
ll kpow(ll a, ll b) {
	ll r = 1;
	for (; b; b >>= 1, a = a * a % P)
		if (b & 1)
			r = r * a % P;
	return r;
}
struct Gauss {
	static const int N = 107;
	int a[N][N];
	int solve(int n, int m) {
		int i = 0, x = 0;
		for (; i < n && x < m; ++i, ++x) {
			int r = i;
			while (r < n && !a[r][x])
				++r;
			if (r < n) {
				if (r != i)
					rep(j, 0, m + 1)
						swap(a[r][j], a[i][j]);
				rep(j, 0, n)
					if (i != j && a[j][x])
						for (int k = m; k >= x; --k)
							a[j][k] = (a[j][k]
									- 1ll * a[i][k] * a[j][x] % P
											* kpow(a[i][x], P - 2) % P + P) % P;
			} else
				--i;
		}
		rep(k, i, n)
			if (a[k][m])
				return -1;
		return m - i;
	}
} G;
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d %s", &P, F);
		n = strlen(F);
		rep(k, 0, n)
		{
			if (F[k] == '*')
				G.a[k][n] = 0;
			else
				G.a[k][n] = F[k] - 'a' + 1;
			ll ki = 1;
			rep(i, 0, n)
			{
				G.a[k][i] = ki;
				ki = (ki * (k + 1)) % P;
			}
		}
		G.solve(n, n);
		rep(i, 0, n)
		{
			if (i)
				putchar(' ');
			int x = 1ll * G.a[i][n] * kpow(G.a[i][i], P - 2) % P;
			printf("%d", x);
		}
		puts("");
	}
	return 0;
}