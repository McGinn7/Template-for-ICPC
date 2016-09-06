#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
const int N = 1e5 + 7;
const int MOD = 1e9 + 7;
//----------head-----------
int n, rt, tot, c[N], r[N], E[N], add[N], ans[N], dep[N], lg[N << 1],
        st[N << 1][22];
vector<int> e[N], g[N];
void init() {
    lg[1] = 0;
    rep(i, 2, N * 2)
        lg[i] = lg[i - 1] + (i == (i & -i));
}
void dfs(int u, int p) {
    ++tot;
    r[u] = tot, st[tot][0] = u;
    g[c[u]].pb(u);
    rep(i, 0, sz(e[u]))
    {
        int v = E[e[u][i]] ^ u;
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
        st[++tot][0] = u;
    }
}
inline int _min(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}
void lca_rmq() {
    for (int j = 1; (1 << j) <= tot; ++j)
        for (int i = 1; i + (1 << j) - 1 <= tot; ++i)
            st[i][j] = _min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int lca(int x, int y) {
    x = r[x], y = r[y];
    if (x > y)
        swap(x, y);
    int k = lg[y - x + 1];
    return _min(st[x][k], st[y - (1 << k) + 1][k]);
}
int sta[N];
void solve(const vector<int> &vec) {
    int top = 0;
    rep(i, 0, sz(vec))
    {
        int u = vec[i];
        if (!top) {
            sta[++top] = u;
            continue;
        }
        vector<int> l;
        int anc = lca(u, sta[top]);
//      printf("lca(%d, %d) = %d\n", u, sta[top], anc);
        while (top && dep[sta[top]] > dep[anc])
            l.pb(sta[top--]);
        if (!top || sta[top] != anc)
            sta[++top] = anc;
        l.pb(sta[top]);
        rep(j, 1, sz(l))
        {
//          printf("l +1 %d, -1 %d\n", l[j - 1], l[j]);
            ++add[l[j - 1]], --add[l[j]];
        }
        sta[++top] = u;
    }
    rep(i, 1, top)
    {
//      printf("s +1 %d, -1 %d\n", sta[i + 1], sta[i]);
        ++add[sta[i + 1]], --add[sta[i]];
    }
}
void DFS(int u, int p) {
    rep(i, 0, sz(e[u]))
    {
        int v = E[e[u][i]] ^ u;
        if (v == p)
            continue;
        DFS(v, u);
        add[u] += add[v];
        ans[e[u][i]] += add[v];
    }
}
int main() {
    init();
    while (~scanf("%d", &n)) {
        rep(i, 1, n + 1)
            scanf("%d", &c[i]);
        rep(i, 1, n + 1)
            add[i] = 0, e[i].clear(), g[i].clear();
        rep(i, 1, n)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            ans[i] = 0, E[i] = u ^ v;
            e[u].pb(i), e[v].pb(i);
        }
        tot = 0, dep[rt = 1] = 0;
        dfs(rt, -1);
        lca_rmq();
        rep(i, 1, n + 1)
            solve(g[i]);
        DFS(rt, -1);
        rep(i, 1, n)
            printf("%d\n", ans[i]);
    }
    return 0;
}