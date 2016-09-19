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
const ul BASE = 1e7 + 7;
const int N = 5e5 + 7;
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
struct Node {
	int p, v, l, r;
	Node() {

	}
	Node(int _p, int _v, int _l, int _r) {
		p = _p, v = _v, l = _l, r = _r;
	}
	bool operator<(const Node& nd) const {
		return p < nd.p;
	}
} q[N * 2], Q[N];
int n, m, t, V[2], L[2], R[2], x[1007], sum[2][1007];
bool ans[N];
int top, DC[N << 2];
struct Fenwick {
	int n, c[N * 4];
	void init(int _n) {
		n = _n;
		rep(i, 0, n + 1)
			c[i] = 0;
	}
	void ins(int i, int v) {
		while (i <= n) {
			c[i] += v;
			i += i & -i;
		}
	}
	int qry(int i) {
		int ret = 0;
		while (i > 0) {
			ret += c[i];
			i -= i & -i;
		}
		return ret;
	}
} fw;
inline void scanf_(int &num) {
	char in;
	while ((in = getchar()) > '9' || in < '0')
		;
	num = in - '0';
	while (in = getchar(), in >= '0' && in <= '9')
		num *= 10, num += in - '0';
}
void _max(int &x, int y) {
	if (x < y)
		x = y;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf_(n);
		scanf_(m);
		V[0] = V[1] = 0;
		rep(i, 1, n + 1)
		{
			scanf_(x[i]);
			rep(j, 0, 2)
				sum[j][i] = sum[j][i - 1];
			sum[1 ^ (i & 1)][i] += x[i];
			_max(V[1 ^ (i & 1)], x[i]);
		}
		t = 0;
		top = 0;
		rep(i, 1, n + 1)
			rep(j, i + 1, n + 1)
			{
				rep(k, 0, 2)
					L[k] = R[k] = sum[k][j - 1] - sum[k][i];
				(i & 1) ? R[0] += x[i] : R[1] += x[i];
				(j & 1) ? R[0] += x[j] : R[1] += x[j];
				q[t++] = Node(L[0], 1, L[1], R[1]);
				q[t++] = Node(R[0] + 1, -1, L[1], R[1]);
				DC[top++] = L[1], DC[top++] = R[1];
			}
		rep(i, 0, m)
		{
			int a, b;
			scanf_(a);
			scanf_(b);
			DC[top++] = b;
			Q[i] = Node(a, b, i, i);
		}
		sort(DC, DC + top);
		top = unique(DC, DC + top) - DC;
		fw.init(top + 1);

		sort(q, q + t), sort(Q, Q + m);
		int j = 0;
		rep(i, 0, m)
			if (Q[i].p > 0 && Q[i].v > 0) {
				while (j < t && q[j].p <= Q[i].p) {
					int l = lower_bound(DC, DC + top, q[j].l) - DC + 1, r =
							lower_bound(DC, DC + top, q[j].r) - DC + 1;
					fw.ins(l, q[j].v);
					fw.ins(r + 1, -q[j].v);
					++j;
				}
				int p = lower_bound(DC, DC + top, Q[i].v) - DC + 1;
				ans[Q[i].l] = (fw.qry(p) > 0);
			} else if (!Q[i].p) {
				ans[Q[i].l] = (V[1] >= Q[i].v);
			} else {
				ans[Q[i].l] = (V[0] >= Q[i].p);
			}
		rep(i, 0, m)
			putchar(ans[i] ? '1' : '0');
		puts("");
	}
	return 0;
}
