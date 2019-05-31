#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
int n, m, S[N], price[N];
ll f[N][N], g[N][N];
vector<int> e[N], t[N], V;
void dfs(int u, int p) {
    rep(i, 0, sz(e[u])) {
        int v = S[e[u][i]] - u;
        if (v == p)
            continue;
        dfs(v, u);
    }
    sort(t[u].begin(), t[u].end());
    int w = sz(t[u]);
    for (int j = sz(V) - 1; j >= 0; --j) {
        while (w > 0 && t[u][w - 1] >= V[j])
            --w;
        f[u][j] = 1ll * (sz(t[u]) - w) * V[j];
        rep(i, 0, sz(e[u])) {
            int v = S[e[u][i]] - u;
            if (v == p)
                continue;
            f[u][j] += f[v][g[v][j]];
        }
        g[u][j] = j;
        if (j + 1 < sz(V) && f[u][g[u][j + 1]] > f[u][j]) 
            g[u][j] = g[u][j + 1];
    }
}
void DFS(int u, int c, int p) {
    rep(i, 0, sz(e[u])) {
        int v = S[e[u][i]] - u;
        if (v == p)
            continue;
        price[e[u][i]] = V[g[v][c]] - V[c];
        DFS(v, g[v][c], u);
    }
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &m);
        rep(i, 0, n)
            e[i].clear(), t[i].clear();
        rep(i, 1, n) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            S[i] = u + v;
            e[u].pb(i), e[v].pb(i);
        }
        V.clear();
        V.pb(0);
        rep(i, 0, m) {
            int C, B;
            scanf("%d%d", &C, &B);
            --C;
            t[C].pb(B), V.pb(B);
        }
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());
        dfs(0, -1);
        DFS(0, 0, -1);
        printf("%lld\n", f[0][0]);
        rep(i, 1, n) {
            if (i - 1)
                putchar(' ');
            printf("%d", price[i]);
        }
        puts("");
    }
    return 0;
}
