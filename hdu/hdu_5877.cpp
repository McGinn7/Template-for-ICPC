#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
const int N = 2e5 + 7;
//-------head---------
struct Node {
	ll v;
	int u;
	Node() {
	}
	Node(int _u, ll _v) {
		u = _u, v = _v;
	}
	bool operator<(const Node &p) const {
		return v < p.v;
	}
} nd[N], qy[N];
struct Fenwick {
	int n, c[N];
	void init(int _n) {
		n = _n, memset(c, 0, sizeof(c[0]) * (n + 2));
	}
	void upd(int i, int v) {
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
int n, m, rt, tot, a[N], L[N], R[N], deg[N];
ll k;
vector<int> e[N];
void dfs(int u) {
	L[u] = ++tot;
	rep(i, 0, sz(e[u])) 
		dfs(e[u][i]);
	R[u] = tot;
}
int main() {
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k;
		rep(i, 0, n)
			cin >> a[i];
		rep(i, 0, n)
			deg[i] = 0, e[i].clear();
		rep(i, 1, n) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			e[u].pb(v), ++deg[v];
		}
		rep(i, 0, n)
			if (!deg[i]) {
				rt = i;
				break;
			}
		tot = 0;
		dfs(rt);
		ll ans = 0;
		m = 0;
		rep(i, 0, n) { 
			if (a[i] == 0) {
				ans += R[i] - L[i];
			} else {
				nd[i] = Node(i, a[i]);
				qy[m++] = Node(i, k / a[i]);
			}
		}
		fw.init(n);
		sort(nd, nd + n), sort(qy, qy + m);
		int nid = 0;
		rep(i, 0, m) {
			while (nid < n && nd[nid].v <= qy[i].v)
				fw.upd(L[nd[nid++].u], 1);
			int u = qy[i].u;
			ans += fw.qry(R[u]) - fw.qry(L[u]);
		}
		cout << ans << endl;
	}
	return 0;
}
