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
const int N = 1e3 + 7;
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
int n, m;
struct Node {
	int w, zone;
	ll x, y;
	Node() {

	}
	Node(ll _x, ll _y) {
		x = _x, y = _y;
		zone = Zone();
	}
	int Zone() {
		if (x > 0 && y >= 0)
			return 0;
		if (y > 0 && x <= 0)
			return 1;
		if (x < 0 && y <= 0)
			return 2;
		return 3;
	}
	ll operator^(const Node &p) const {
		return x * p.y - y * p.x;
	}
	bool operator<(const Node &p) const {
		if (x != p.x)
			return x < p.x;
		return y < p.y;
	}
} a[N], b[N];
bool cmp(const Node &p, const Node &q) {
	if (p.zone != q.zone)
		return p.zone < q.zone;
	if ((p ^ q) != 0)
		return (p ^ q) > 0;
	return sqr(p.x) + sqr(p.y) < sqr(q.x) + sqr(q.y);
}
void inc(int &x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}
int calc(int t, int d) {
	int ret = kpow(2, t, MOD) - d;
	inc(ret, MOD);
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		rep(i, 0, n)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[i] = Node(x, y);
		}
		sort(a, a + n);
		m = 1, a[0].w = 1;
		rep(i, 1, n)
			if (a[m - 1].x == a[i].x && a[m - 1].y == a[i].y) {
				++a[m - 1].w;
			} else {
				a[m] = a[i];
				a[m++].w = 1;
			}
		n = m;
		int ans = 0;
		rep(i, 0, n)
		{
			inc(ans, calc(a[i].w, 1 + a[i].w) * 2 % MOD);
			m = 0;
			rep(j, 0, n)
				if (j != i) {
					b[m] = Node(a[j].x - a[i].x, a[j].y - a[i].y);
					b[m++].w = a[j].w;
				}
			sort(b, b + m, cmp);
			int l = 0, L = calc(a[i].w, 1);
			while (l < m) {
				int tot = 0, r = l + 1;
				while (r < m && (b[l] ^ b[r]) == 0 && b[r].zone == b[l].zone)
					++r;
				while (l < r) {
					inc(ans,
							1ll * L * kpow(2, tot, MOD) % MOD * calc(b[l].w, 1)
									% MOD);
					tot += b[l++].w;
				}
			}
		}
		printf("%I64d\n", 1ll * ans * kpow(2, MOD - 2, MOD) % MOD);
	}
	return 0;
}
