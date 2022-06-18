#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cerr<<#x<<"="<<x<<","
#define de(x) cerr<<#x<<"="<<x<<endl
//-------
 
const int N = 51;
 
int n, m, w[N], g[N][N];
bool vis[N], used[N];
 
int f[N], G[N][N], ID[N][N];
 
int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}
 
int argmax(int n, int *a, bool *v) {
	pair<int, int> rec(INT_MIN, 0);
	rep(i, 0, n) if (!v[i]) 
		rec = max(rec, make_pair(a[i], i));
	return rec.second;
}
 
int phase(int A, int &s, int &t) {
	rep(i, 0, n)
		w[i] = 0, vis[i] = used[i];
	rep(_, A, n) {
		s = t;
		t = argmax(n, w, vis);
		vis[t] = true;	
		rep(i, 0, n) if (!vis[i]) w[i] += g[i][t];
	}
	return w[t];
}
 
void merge(int s, int t) {
	used[t] = true, f[get(t)] = get(s);
	rep(i, 0, n) {
		g[i][s] += g[i][t];
		g[s][i] += g[t][i];
	}
}
 
pair<int, vector<int>> mincut(int cc) {
	pair<int, vector<int>> ans(INT_MAX, {});	
	rep(i, 1, n - 1) {
		int s, t;
		int cost = phase(i, s, t);
		if (cost < ans.first) {
			vector<int> A, B, E;
			rep(j, 0, n) if (get(j) != get(t)) {
				if (j != cc) A.push_back(j);
			} else {
				B.push_back(j);
			}
			for (auto a: A) for (auto b: B)
				if (ID[a][b]) E.push_back(ID[a][b]);
			ans = make_pair(cost, E);
		}
		merge(s, t);
	}
	return ans;
}
 
void solve() {
	pair<int, vector<int>> ans(INT_MAX, {});
	rep(cc, 0, n) {
		rep(i, 0, n) rep(j, 0, n) g[i][j] = G[i][j];
		rep(i, 0, n) g[i][cc] = g[cc][i] = 0;
		rep(i, 0, n) f[i] = i, used[i] = false;
		used[cc] = true;	
 
		ans = min(ans, mincut(cc));		
	}
	printf("%d\n", ans.first);
	const auto &edges = ans.second;	
	printf("%d\n", edges.size());
	rep(i, 0, edges.size()) {
		if (i) putchar(' ');
		printf("%d", edges[i]);
	}
}
 
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 0, m) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		--a, --b;
		G[a][b] = G[b][a] = c;	
		ID[a][b] = ID[b][a] = i + 1;
	}
 
	solve();
 
	return 0;
}
