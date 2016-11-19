const int N = 2e5 + 7;
const int K = 2;
int n, m, dim, c[N];
struct Node {
	int id, x[K];
	void in() {
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
			return -1;
		int t, m;
		t = m = (l + r) >> 1, dim = dep % K;
		nth_element(a + l, a + m, a + r + 1);
		ch[t][0] = build(l, m - 1, dep + 1);
		ch[t][1] = build(m + 1, r, dep + 1);
		rep(i, 0, K)
			mn[t][i] = mx[t][i] = a[m].x[i];
		rep(i, 0, 2) 
			if (~ch[t][i]) {
				rep(j, 0, K) {
					mn[t][j] = min(mn[t][j], mn[ch[t][i]][j]);
					mx[t][j] = max(mx[t][j], mx[ch[t][i]][j]);
				}
			}
		return t;
	}
	ll dis, qc;
	Node q, ans;
	ll h(int t) {
		if (t < 0)
			return 1e18;
		ll ret = 0;
		rep(i, 0, K) {
			if (q.x[i] < mn[t][i])
				ret += sqr(mn[t][i] - q.x[i]);
			if (q.x[i] > mx[t][i])
				ret += sqr(mx[t][i] - q.x[i]);
		}
		return ret;
	}
	void upd(const Node &p) {
		if (c[p.id] > qc) 
			return ;
		ll _dis = 0;
		rep(i, 0, K)
			_dis += sqr(p.x[i] - q.x[i]);
		if (_dis < dis || (_dis == dis && p.id < ans.id))
			dis = _dis, ans = p;
	}
	void qry(int l, int r, int dep) { // Remember Initialize: dis, q and so on
		if (l > r)
			return ;
		int t, m;
		t = m = (l + r) >> 1;
		upd(a[m]);
		ll hl = h(ch[t][0]), hr = h(ch[t][1]);
		if (hl < hr) {
			if (hl <= dis)
				qry(l, m - 1, dep + 1);
			if (hr <= dis)
				qry(m + 1, r, dep + 1);
		} else {
			if (hr <= dis)
				qry(m + 1, r, dep + 1);
			if (hl <= dis)
				qry(l, m - 1, dep + 1);
		}
	}
} kd;
