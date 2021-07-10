#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<int>> VII;
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)
#define per(i, l, r) for (int i = (r)-1; i >= (l); --i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
const int P = 1e9 + 7;
inline void inc(int &x, int y) {
	if ((x += y) >= P) x -= P;
}
template <typename T>
vector<vector<T>> VV(int n, int m, T v) {
	return vector<vector<T>>(n, vector<T>(m, v));
}
//-------

const int N = 1e5 + 7;

struct Node {
	int id, sgn, pos;
	Node() {}
	Node(int id, int sgn, int pos) : id(id), sgn(sgn), pos(pos) {}
	bool operator<(const Node &p) const { return pos < p.pos; }
} a[N * 2];

struct FenwickTree {
	int n;
	vector<ll> c;
	void init(int _n) {
		n = _n;
		c.resize(n + 1, 0);
	}
	void upd(int i, ll v) {
		while (i < sz(c)) {
			c[i] += v;
			i += i & -i;
		}
	}
	ll sum(int i) {
		ll r = 0;
		while (i > 0) {
			r += c[i];
			i -= i & -i;
		}
		return r;
	}

} fwt_l, fwt_w;

int n, L, S[N * 2], rk[N * 2];
ll C[N];

int main() {
	scanf("%d%d", &n, &L);
	rep(i, 1, 2 * n + 1) {
		scanf("%d", &a[i].pos);
		a[i].id = i <= n ? i : i - n;
		a[i].sgn = i <= n ? 1 : -1;
	}
	n *= 2;
	sort(a + 1, a + n + 1);
	rep(i, 1, n + 1) {
		a[n + i].pos = a[i].pos + L;
		a[n + i].id = a[i].id;
		a[n + i].sgn = a[i].sgn;
	}

	int nn = 2 * n;
	rep(i, 1, nn + 1) S[i] = S[i - 1] + a[i].sgn;
	rep(i, 0, nn + 1) rk[i] = i;
	sort(rk, rk + nn + 1, [](int i, int j) { return S[i] > S[j]; });

	fwt_l.init(nn);
	fwt_w.init(nn);
	rep(j, 0, nn + 1) {
		int i = rk[j];
		if (0 < i && i < nn) {
			int L_i = a[i + 1].pos - a[i].pos;
			fwt_l.upd(i, L_i);
			fwt_w.upd(i, 1ll * L_i * S[i]);
		}
		if (i < n) {
			C[i + 1] = fwt_w.sum(i + n - 1) - fwt_w.sum(i);
			C[i + 1] -= (fwt_l.sum(i + n - 1) - fwt_l.sum(i)) * S[i];
		}
	}

	pair<ll, int> ans(LLONG_MAX, INT_MAX);
	ll sum_l = 0, sum_w = 0;
	auto f_cost = [&sum_l, &sum_w](int i, int sgn = 1) {
		int L_i = a[i + 1].pos - a[i].pos;
		sum_l += sgn * L_i;
		sum_w += 1ll * sgn * L_i * S[i];
	};
	rep(j, 1, nn - 1) {
		f_cost(j);
		int i = j - (n - 1) + 1;
		if (i > 1) f_cost(i - 1, -1);
		if (i > 0) {
			ll _cost = sum_w - sum_l * S[i - 1];
			ll cost = C[i] - (_cost - C[i]);
			ans = min(ans, make_pair(cost, i));
		}
	}

	deque<int> dq;
	for (int i = 0, j = ans.second; i < n; ++i, ++j) {
		if (dq.empty() || a[dq.front()].sgn == a[j].sgn)
			dq.push_back(j);
		else {
			if (1 == a[j].sgn)
				rk[a[j].id] = a[dq.front()].id;
			else
				rk[a[dq.front()].id] = a[j].id;
			dq.pop_front();
		}
	}
	printf("%lld\n", ans.first);
	rep(i, 1, n / 2 + 1) {
		if (i > 1) printf(" ");
		printf("%d", rk[i]);
	}
	return 0;
}
