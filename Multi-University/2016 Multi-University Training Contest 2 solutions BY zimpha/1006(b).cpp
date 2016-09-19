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
#include<string>
#include<sstream>
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
const ul BASE = 1e6 + 7;
const int N = 2e5 + 7;
const int M = 5e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-9;
ll kpow(ll a, ll b, ll mod) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1)
			ret = ret * a % mod;
	return ret;
}
//--------------head-------------
int n, m, ans, sum, w[N], u[N * 2], v[N * 2];
int f[N], d[N], val[N];
int top;
struct Record {
	int x, y, d, v;
} rec[N];
int nt, head[N];
struct Node {
	int id, nxt;
} nd[N * 20];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
void addLink(int d, int id) {
	nd[nt].id = id, nd[nt].nxt = head[d], head[d] = nt++;
}
int get(int x) {
	while (x != f[x])
		x = f[x];
	return x;
}
void record(int x, int y) { // d[x] < d[y]
	++top;
	rec[top].x = x, rec[top].y = y, rec[top].d = d[y], rec[top].v = val[y];
	f[x] = y, d[y] = max(d[y], d[x] + 1), val[y] = 1ll * val[y] * val[x] % MOD;
}
void merge(int x, int y) {
	x = get(x), y = get(y);
	if (x != y) {
		inc(sum, (1ll * val[x] * val[y] + MOD - val[x] + MOD - val[y]) % MOD);
		d[x] < d[y] ? record(x, y) : record(y, x);
	}
}
void undo(int ver) {
	int _x, _y, _d, _v;
	while (top > ver) {
		_x = rec[top].x, _y = rec[top].y, _d = rec[top].d, _v = rec[top].v;
		inc(sum, MOD - val[_y]);
		f[_x] = _x, f[_y] = _y, d[_y] = _d, val[_y] = _v;
		inc(sum, val[_x]), inc(sum, val[_y]);
		--top;
	}
}
void solve(int l, int r, int dep) {
	if (l == r) {
		inc(ans, 1ll * (l + 1) * (sum - w[l] + MOD) % MOD);
		return;
	}
	int _nt = nt, _top = top, mid = (l + r) >> 1;
	head[dep + 1] = -1;
	for (int i = head[dep]; ~i; i = nd[i].nxt) {
		int id = nd[i].id;
		if (v[id] < l || mid < u[id] || (u[id] < l && mid < v[id])) {
			merge(u[id], v[id]);
		} else {
			addLink(dep + 1, id);
		}
	}
	solve(l, mid, dep + 1);
	undo(_top), nt = _nt, head[dep + 1] = -1;
	++mid;
	for (int i = head[dep]; ~i; i = nd[i].nxt) {
		int id = nd[i].id;
		if (v[id] < mid || r < u[id] || (u[id] < mid && r < v[id])) {
			merge(u[id], v[id]);
		} else {
			addLink(dep + 1, id);
		}
	}
	solve(mid, r, dep + 1);
	undo(_top), nt = _nt, head[dep + 1] = -1;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		sum = 0;
		rep(i, 0, n)
		{
			scanf("%d", &w[i]);
			inc(sum, w[i]);
			f[i] = i, d[i] = 0, val[i] = w[i];
		}
		nt = 0, head[0] = -1;
		rep(i, 0, m)
		{
			scanf("%d%d", &u[i], &v[i]), --u[i], --v[i];
			if (u[i] > v[i])
				swap(u[i], v[i]);
			addLink(0, i);
		}
		top = 0, ans = 0;
		solve(0, n - 1, 0);
		printf("%d\n", ans);
	}
	return 0;
}
