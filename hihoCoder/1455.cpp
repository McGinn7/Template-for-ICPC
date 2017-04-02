#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 5e4 + 7;
int n, B, tot, w[N], L[N], R[N], id[N];
vector<int> e[N];
int cnt[N], cnt_all[N];
bitset<N> ret, bit[2], bit_all[2];
struct Query {
	int l, r, w;
	Query() {
	}
	Query(int _l, int _r, int _w) {
		l = _l, r = _r, w = _w;
	}
	bool operator<(const Query &q) const {
		return r < q.r;	
	}
};
vector<Query> q[N];
void init() {
	rep(i, 0, 2)
		bit[i].reset(), bit_all[i].reset();
	rep(i, 1, n + 1)
		cnt[i] = cnt_all[i] = 0;
	rep(i, 1, n + 1) {
		++cnt_all[w[i]];		
		if (cnt_all[w[i]] == 1) 
			bit_all[0][N - w[i]] = bit_all[1][w[i]] = 1;
	}
}
void upd(int w, int add) {
	cnt[w] += add;	
	bit[0][N - w] = bit[1][w] = (cnt[w] > 0);
	cnt_all[w] -= add;
	bit_all[0][N - w] = bit_all[1][w] = (cnt_all[w] > 0);
}
set<int> S[N];
set<int>::iterator it;
void merge(set<int> &s1, set<int> &s2, int w) {
	if (sz(s1) < sz(s2))
		swap(s1, s2);
	int d;
	for (it = s2.begin(); it != s2.end(); ++it) {
		int d = *it - w;
		if (d > 0 && s1.find(w - d) != s1.end())
			ret[d] = 1;
		d = w - *it;
		if (d > 0 && s1.find(w + d) != s1.end())
			ret[d] = 1;
	}
	for (it = s2.begin(); it != s2.end(); ++it) 
		s1.insert(*it);
	s2.clear();
}
void DFS(int u, int p) {
	L[u] = ++tot;
	id[L[u]] = u;
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p)
			continue;
		DFS(v, u);		
		merge(S[u], S[v], w[u]);
	}
	R[u] = tot, S[u].insert(w[u]);
}
void moDui() {
	init(), B = sqrt(n + 0.5);
	rep(i, 1, n + 1) 
		if (R[i] - L[i] + 1 <= B) {	
			rep(j, L[i], R[i] + 1) upd(w[id[j]], 1);
			ret |= (bit[0] >> (N - w[i])) & (bit_all[1] >> w[i]);
			ret |= (bit_all[0] >> (N - w[i])) & (bit[1] >> w[i]);
			rep(j, L[i], R[i] + 1) upd(w[id[j]], -1);
		} else {
			int bid = L[i] / B + 1;	
			q[bid].push_back(Query(L[i], R[i], w[i]));
		}
	for (int i = 0; i * B + 1 <= n; ++i) {
		if (!sz(q[i]))
			continue;
		sort(q[i].begin(), q[i].end());
		int j = i * B + 1, k = 0;
		while (j <= n && k < sz(q[i])) {
			upd(w[id[j]], 1);
			while (k < sz(q[i]) && j == q[i][k].r) {	
				for (int p = i * B; p >= q[i][k].l; --p) upd(w[id[p]], 1);
				int _w = q[i][k].w;
				ret |= (bit[0] >> (N - _w)) & (bit_all[1] >> _w);
				ret |= (bit_all[0] >> (N -_w)) & (bit[1] >> _w);
				for (int p = i * B; p >= q[i][k].l; --p) upd(w[id[p]], -1);
				++k;
			}
			++j;
		}
		for (--j; j >= i * B + 1; --j)
			upd(w[id[j]], -1);
	}

}
int main() {
	scanf("%d", &n);
	rep(i, 1, n + 1)
		scanf("%d", &w[i]);
	rep(i, 1, n) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	DFS(1, -1);
	moDui();
	ret[0] = 0;
	printf("%d\n", int(ret.count()));
	return 0;
}
