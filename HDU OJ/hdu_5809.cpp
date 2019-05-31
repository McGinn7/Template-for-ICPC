#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = ~0ULL >> 1;
const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
const int K = 2;
int dim;
struct Node {
	int id, x[K];
	void in(int _id) {
		id = _id;
		rep(i, 0, K)
			scanf("%d", &x[i]);
	}
	bool operator<(const Node &p) const {
		return x[dim] < p.x[dim];
	}
} a[N];
struct KdTree {
	int ch[N][2], mn[N][K], mx[N][K];
	inline ll sqr(ll x) {
		return x * x;
	}
	int build(int l, int r, int dep) {
		if (l > r)
			return 0;
		int t, m;
		t = m = (l + r) >> 1, dim = dep % K;
		nth_element(a + l, a + m, a + r + 1);
		ch[t][0] = build(l, m - 1, dep + 1), ch[t][1] = build(m + 1, r, dep + 1);
		rep(i, 0, K)
			mn[t][i] = mx[t][i] = a[m].x[i];
		rep(i, 0, 2)
			rep(j, 0, K)
				if (ch[t][i]) {
					mn[t][j] = min(mn[t][j], mn[ch[t][i]][j]);
					mx[t][j] = max(mx[t][j], mx[ch[t][i]][j]);
				}
		return t;
	}
	ll L;
	int qid, aid, ax, ay;
	ll h(int t) {
		if (!t)
			return LINF;
		ll ret = 0;
		rep(i, 0, K)
		{
			if (a[qid].x[i] < mn[t][i])
				ret += sqr(mn[t][i] - a[qid].x[i]);
			if (mx[t][i] < a[qid].x[i])
				ret += sqr(a[qid].x[i] - mx[t][i]);
		}
		return ret;
	}
	void query(int l, int r, int dep) {
		if (l > r)
			return;
		int t, m;
		t = m = (l + r) >> 1;
		if (m != qid) {
			ll D = 0;
			rep(i, 0, K)
				D += sqr(a[qid].x[i] - a[m].x[i]);
			if (D < L || (D == L && a[m].x[0] < ax)
					|| (D == L && a[m].x[0] == ax && a[m].x[1] < ay))
				L = D, ax = a[m].x[0], ay = a[m].x[1], aid = a[m].id;
		}
		ll hl = h(ch[t][0]), hr = h(ch[t][1]);
		if (hl < hr) {
			if (hl <= L)
				query(l, m - 1, dep + 1);
			if (hr <= L)
				query(m + 1, r, dep + 1);
		} else {
			if (hr <= L)
				query(m + 1, r, dep + 1);
			if (hl <= L)
				query(l, m - 1, dep + 1);
		}
	}
} kd;
int n, q, f[N];
int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}
int main() {
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &q);
		rep(i, 1, n + 1)
			f[i] = i, a[i].in(i);
		kd.build(1, n, 0);
		rep(i, 1, n + 1)
		{
			kd.L = LINF, kd.qid = i, kd.aid = 0;
			kd.query(1, n, 0);
			f[get(a[i].id)] = get(kd.aid);
			assert(kd.aid != 0);
//		printf("f[%d] = %d\n", a[i].id, a[kd.aid].id);
		}
		printf("Case #%d:\n", cas + 1);
		rep(i, 0, q)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			puts(get(x) == get(y) ? "YES" : "NO");
		}
	}
	return 0;
}