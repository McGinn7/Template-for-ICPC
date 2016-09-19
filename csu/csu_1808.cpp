#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = 1e16 + 7;
const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
struct Edge {
    int a, b, c, t;
    void in() {
        scanf("%d%d%d%d", &a, &b, &c, &t);
        --a, --b;
    }
    bool operator<(const Edge &p) const {
        return c < p.c;
    }
} E[N];
int n, m, tot;
vector<pii> r[N], e[N];
void addEdge(int s, int t, int w) {
    e[s].pb(mp(t, w)), e[t].pb(mp(s, w));
}
void upd(int u, int c) {
    if (r[u].empty() || r[u].back().first != c) {
        e[tot].clear();
        if (!r[u].empty())
            addEdge(r[u].back().second, tot, c - r[u].back().first);
        r[u].pb(mp(c, tot++));
    }
}
ll dis[N];
priority_queue<pair<ll, int> > que;
ll solve() {
    while (!que.empty())
        que.pop();
    fill_n(dis, tot, LINF);
    rep(i, 0, sz(r[0]))
    {
        int u = r[0][i].second;
        que.push(mp(0, u));
    }
    while (!que.empty()) {
        int u = que.top().second;
        ll d = -que.top().first;
        que.pop();
        if (d >= dis[u])
            continue;
//      printf("que %d %I64d\n", u, d);
        dis[u] = d;
        rep(i, 0, sz(e[u]))
        {
            int v = e[u][i].first;
            que.push(mp(-d - e[u][i].second, v));
        }
    }
    ll ans = LINF;
    rep(i, 0, sz(r[n - 1]))
        ans = min(ans, dis[r[n - 1][i].second]);
    return ans;
}
int main() {
//  freopen("data.in", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        tot = 0;
        rep(i, 0, n)
            r[i].clear(), e[i].clear();
        rep(i, 0, m)
            E[i].in();
        sort(E, E + m);
        rep(i, 0, m)
        {
            int u = E[i].a, v = E[i].b;
            upd(u, E[i].c), upd(v, E[i].c);
            addEdge(r[u].back().second, r[v].back().second, E[i].t);
        }
        printf("%lld\n", solve());
    }
    return 0;
}