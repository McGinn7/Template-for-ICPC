#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<int>> VII;
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
const int P = 1e9 + 7;
inline void inc(int &x, int y) { if ((x += y) >= P) x -= P;}
template<typename T>
vector<vector<T>> VV(int n, int m, T v) {
  return vector<vector<T>>(n, vector<T>(m, v));
}
//-------
 
const int N = 107;
const int M = 6e3 + 7;
const int INF = N * M;
 
int n, m, A, B, deg[N];
vector<int> a;
vector<pair<int, int>> e[N];
 
struct MaxFlow {
	int n, et, dis[N], que[N], cur[N], head[N];
	struct Edge {
		int s, t, v, nxt;
		Edge() {
		}
		Edge(int _s, int _t, int _v, int _nxt) {
			s = _s, t = _t, v = _v, nxt = _nxt;
		}
	} e[M * 2];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(head[0]) * n);
	}
	void addEdge(int s, int t, int v) {
		e[et] = Edge(s, t, v, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		int qh = 0, qt = 0;
		memset(dis, -1, sizeof(dis[0]) * n);
		dis[S] = 0, que[qt++] = S;
		while (qh < qt)
			for (int i = head[que[qh++]]; ~i; i = e[i].nxt)
				if (e[i].v && !~dis[e[i].t]) {
					dis[que[qt++] = e[i].t] = 1 + dis[e[i].s];
					if (e[i].t == T)
						return true;
				}
		return false;
	}
	ll dinic(int S, int T) {
		int u, qt;
		ll maxflow = 0;
		while (bfs(S, T)) {
			memcpy(cur, head, sizeof(cur[0]) * n);
			u = S, qt = 0;
			while (~cur[S]) {
				if (u == T) {
					ll flow = LLONG_MAX;
					for (int i = qt - 1; i >= 0; --i)
						flow = min(flow, (ll) e[que[i]].v);
					for (int i = qt - 1; i >= 0; --i) {
						e[que[i]].v -= flow, e[que[i] ^ 1].v += flow;
						if (!e[que[i]].v)
							qt = i;
					}
					u = e[que[qt]].s, maxflow += flow;
				} else if (~cur[u] && e[cur[u]].v
						&& dis[u] + 1 == dis[e[cur[u]].t]) {
					que[qt++] = cur[u];
					u = e[cur[u]].t;
				} else {
					while (u != S && !~cur[u])
						u = e[que[--qt]].s;
					cur[u] = e[cur[u]].nxt;
				}
			}
		}
		return maxflow;
	}
} G;
 
void dfs(int u) {
  for (auto &p : e[u]) {
    while (p.second-- > 0) {
      dfs(p.first);
    }
  }
  a.emplace_back(u);
}
 
void solve() {
  scanf("%d%d%d%d", &n, &m, &A, &B);
  int S = n + 1, T = n + 2;
  G.init(n + 3);
  rep(i, 0, m) {
    int x, y, w, t; scanf("%d%d%d%d", &x, &y, &w, &t);
    if (1 == t) { 
      deg[x] -= w, deg[y] += w;
      e[x].emplace_back(y, w);
    } else
      G.addEdge(x, y, w);
  }
  int sum_pos_deg = 0;
  rep(i, 1, n + 1) if (deg[i] > 0) {
    sum_pos_deg += deg[i];
    G.addEdge(S, i, deg[i]);
  } else if (deg[i] < 0) {
    G.addEdge(i, T, -deg[i]);
  }
  G.addEdge(B, A, INF);
  int max_flow = G.dinic(S, T);
  if (max_flow != sum_pos_deg) {
    printf("0");
    return ;
  }
  // delete B->A
  int ans = G.e[G.et - 1].v;
  G.e[G.et - 1].v = G.e[G.et - 2].v = 0;
  ans += G.dinic(A, B);
  if (ans == 0) {
    printf("0");
    return ;
  }
 
  rep(i, 0, G.et) if (~i & 1) {
    int x = G.e[i].s, y = G.e[i].t;
    if (x == S || y == T) continue;
    if (G.e[i^1].v > 0) {
      e[x].emplace_back(y, G.e[i^1].v);
    }
  }
  e[B].emplace_back(A, ans - 1);
  dfs(A);
  reverse(a.begin(), a.end());
  
  int L = a.size();
  rep(i, 1, L)
    if (a[i - 1] == B && a[i] == A) { 
      vector<int> b;
      rep(j, i, L) b.emplace_back(a[j]);
      rep(j, 0, i) b.emplace_back(a[j]);
      swap(a, b);
      break;
    }
  printf("%d\n", ans);
  bool flag = false;
  rep(i, 0, L) { 
    flag ? printf(" ") : flag = true;
    printf("%d", a[i]);
    if (ans > 1 && i + 1 < L && a[i] == B && a[i + 1] == A) {
      printf("\n");
      --ans, flag = false;
    }
  }
}
 
int main() {
  solve();
  return 0;
}
