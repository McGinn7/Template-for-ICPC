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
const int N = 2e5 + 7;
//-------------head------------
int n, m, src, dis[N];
set<int> S;
set<int>::iterator it;
vector<int> e[N];
void out() {
    bool flag = false;
    rep(i, 0, n)
        if (i != src) {
            flag ? putchar(' ') : flag = true;
            printf("%d", dis[i]);
        }
    puts("");
}
queue<pair<int, pii> > que;
void solve() {
    rep(i, 0, n) {
        sort(e[i].begin(), e[i].end());
        e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
    }
    rep(i, 0, n)
        if (e[i].empty()) {
            rep(j, 0, n)
                dis[j] = 1;
            rep(j, 0, sz(e[src]))
                ++dis[e[src][j]];
            out();
            return ;
        }
    memset(dis, -1, sizeof(dis));
    S.clear();
    rep(i, 0, n)
        S.insert(i);
    que.push(mp(0, mp(src, src)));
    while (!que.empty()) {
        int d = que.front().first;
        pii nd = que.front().second;
        que.pop();
        it = S.lower_bound(nd.first);
        while (it != S.end() && (*it) <= nd.second) {
            int u = *it, pre = 0;
            dis[u] = d;
            rep(i, 0, sz(e[u])) {
                int v = e[u][i];
                if (pre < v)
                    que.push(mp(d + 1, mp(pre, v - 1)));
                pre = v + 1;
            }
            if (pre < n)
                que.push(mp(d + 1, mp(pre, n)));
            ++it;
            S.erase(u);
        }
    }
    out();
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &m);
        rep(i, 0, n)
            e[i].clear();
        rep(i, 0, m) {
            int u, v;
            scanf("%d%d", &u, &v), --u, --v;
            if (u == v)
                continue;
            e[u].pb(v), e[v].pb(u);
        }
        scanf("%d", &src), --src;
        solve();
    }
    return 0;
}
