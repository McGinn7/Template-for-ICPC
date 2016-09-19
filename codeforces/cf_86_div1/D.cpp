#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<set>
#include<map>
#include<queue>
#include<bitset>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i,l,r) for(int i=l;i<(r);++i)
#define per(i,l,r) for(int i=r-1;i>=(l);--i)
#define sz(x) ((int)((x).size()))
#define sqr(x) ((ll)(x)*(x))
#define all(x) (x).begin(),(x).end()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define de(x) cout << #x << " = " << x << endl;
#define debug(x) freopen(x".in", "r", stdin);
#define setIO(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
const ll LINF = 1e18 + 7;
const ul BASE = 33;
const int N = 24;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-8;
ll kpow(ll a, ll b) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1)
			ret = ret * a;
	return ret;
}
//--------------head--------------
int n, m, a, b, deg[N], d[N][N];
double f[N][N], g[N * N][N * N];
int main() {
	scanf("%d%d%d%d", &n, &m, &a, &b);
	--a, --b;
	rep(i, 0, m)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		++deg[u], ++deg[v], d[u][v] = d[v][u] = 1;
	}
	rep(i, 0, n)
		scanf("%lf", &f[i][i]);
	rep(i, 0, n)
		rep(j, 0, n)
			if (i != j && d[i][j])
				f[i][j] = (1.0 - f[i][i]) / deg[i];
	rep(i, 0, n)
		rep(j, 0, n)
		{
			g[i * n + j][i * n + j] = -1;
			rep(x, 0, n)
				rep(y, 0, n)
					if (x != y) {
						g[i * n + j][x * n + y] += f[x][i] * f[y][j];
					}
		}
	int NN = n * n;
	g[a * n + b][NN] = -1.0;
	rep(i, 0, NN)
	{
		int r = i;
		rep(j, i + 1, NN)
			if (fabs(g[j][i]) > fabs(g[r][i]))
				r = j;
		rep(j, i, NN + 1)
			swap(g[i][j], g[r][j]);
		double tmp = g[i][i];
		rep(j, i, NN + 1)
			g[i][j] /= tmp;
		rep(k, 0, NN)
			if (i != k) {
				tmp = g[k][i];
				rep(j, i, NN + 1)
					g[k][j] -= tmp * g[i][j];
			}
	}
	rep(i, 0, n) {
		if (i)
			putchar(' ');
		printf("%.10lf", g[i * n + i][NN]);
	}
	return 0;
}
