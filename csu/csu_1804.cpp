#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
const int N = 1e5 + 7;
const int MOD = 1e9 + 7;
//----------head-----------
int n, m, ans, a[N], b[N], f[N], deg[N];
int et, head[N];
struct Edge {
    int t, nxt;
    Edge() {
    }
    Edge(int _t, int _nxt) {
        t = _t, nxt = _nxt;
    }
} e[N];
void addEdge(int s, int t) {
    e[et] = Edge(t, head[s]), head[s] = et++;
}
inline void inc(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}
void dfs(int u) {
    if (~f[u])
        return;
    f[u] = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].t;
        dfs(v);
        inc(f[u], f[v]);
    }
    inc(ans, (ll) f[u] * a[u] % MOD);
    inc(f[u], b[u]);
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        rep(i, 1, n + 1)
            scanf("%d%d", &a[i], &b[i]);
        et = 0;
        rep(i, 1, n + 1)
            f[i] = -1, deg[i] = 0, head[i] = -1;
        rep(i, 0, m)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            ++deg[v], addEdge(u, v);
        }
        ans = 0;
        rep(i, 1, n +1)
            if (!deg[i])
                dfs(i);
        printf("%d\n", ans);
    }
    return 0;
}