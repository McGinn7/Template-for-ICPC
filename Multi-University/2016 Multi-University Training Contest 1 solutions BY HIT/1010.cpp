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
const ul BASE = 1e6 + 7;
const int N = 1e5 + 7;
const int P = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-10;
ll kpow(ll a, ll b) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1)
            ret = ret * a % MOD;
    return ret;
}
//--------------head--------------
int n, t;
char a[20], b[20], name[2][N][12];
vi e[2][N];
map<string, int> m[2];
int get(int i, char s[]) {
    if (m[i].find(s) == m[i].end())
        strcpy(name[i][t], s), m[i][s] = t++;
    return m[i][s];
}
//void dfs(const vi e[], int u, int p) {
//    rep(i, 0, sz(e[u]))
//    {
//        int v = e[u][i];
//        if (v == p)
//            continue;
//        dfs(e, v, u);
//    }
//}
vi R, GR[2];
int root, size, f[N], siz[N];
void getRoot(const vi e[], int u, int p) {
    f[u] = 0, siz[u] = 1;
    rep(i, 0, sz(e[u]))
    {
        int v = e[u][i];
        if (v == p)
            continue;
        getRoot(e, v, u);
        siz[u] += siz[v], f[u] = max(f[u], siz[v]);
    }
    f[u] = max(f[u], size - siz[u]);
//    printf("%d, siz = %d, max = %d\n", u, siz[u], f[u]);
    if (f[u] < f[root]) {
        R.clear();
        R.pb(root = u);
    } else if (f[u] == f[root] && u != root) {
        R.pb(u);
    }
}
ul hs[2][N];
ul dfs(const vi e[], ul h[], int u, int p) {
    siz[u] = 1;
    vector<ul> vec;
    rep(i, 0, sz(e[u]))
    {
        int v = e[u][i];
        if (v == p)
            continue;
        vec.pb(dfs(e, h, v, u));
        siz[u] += siz[v];
    }
    ul ret = siz[u];
    sort(all(vec));
    rep(i, 0, sz(vec))
        ret = ret * BASE + vec[i];
    return h[u] = ret;
}
void DFS(int x, int px, int y, int py) {
//    printf("%d(%s) - %d(%s)\n", x, name[0][x], y, name[1][y]);
    printf("%s %s\n", name[0][x], name[1][y]);
    vector<pair<ul, int> > vx, vy;
    rep(i, 0, sz(e[0][x]))
    {
        int v = e[0][x][i];
        if (v == px)
            continue;
        vx.pb(mp(hs[0][v], i));
    }
    rep(i, 0, sz(e[1][y]))
    {
        int v = e[1][y][i];
        if (v == py)
            continue;
        vy.pb(mp(hs[1][v], i));
    }
    sort(all(vx)), sort(all(vy));
    rep(i, 0, sz(vx))
        DFS(e[0][x][vx[i].se], x, e[1][y][vy[i].se], y);
}
void solve() {
    if (n == 1) {
        puts("a a");
        return;
    }
    rep(i, 0, sz(GR[0]))
        rep(j, 0, sz(GR[1]))
            if (dfs(e[0], hs[0], GR[0][i], -1)
                    == dfs(e[1], hs[1], GR[1][j], -1)) {
//                printf("%d(%s) %d(%s)\n", GR[0][i], name[0][GR[0][i]], GR[1][j],
//                        name[1][GR[1][j]]);
                DFS(GR[0][i], -1, GR[1][j], -1);
                return;
            }
}
int main() {
//    debug("data");
    while (~scanf("%d", &n)) {
        rep(g, 0, 2)
        {
            t = 0, m[g].clear();
            rep(i, 0, n)
                e[g][i].clear();
            rep(i, 1, n)
            {
                scanf(" %s %s", a, b);
                int x = get(g, a), y = get(g, b);
                e[g][x].pb(y), e[g][y].pb(x);
            }
            R.clear(), GR[g].clear();
            root = n, size = n, f[n] = INF;
            getRoot(e[g], 0, -1);
            rep(i, 0, sz(R))
                GR[g].pb(R[i]);
//            printf("root(%d):", g);
//            rep(i, 0, sz(R))
//                printf(" %d", R[i]);
//            puts("");
        }
        solve();
//        puts("");
    }
    return 0;
}
/*
 6
 a b
 a c
 a e
 e f
 e d

 a b
 a d
 a e
 b c
 b f

 */