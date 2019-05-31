#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
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
const ll LINF = 1e10 + 7;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1000000007;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    FastIO() :
            wpos(0) {
    }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len)
            return -1;
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32)
            c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar())
            x = x * 10 + c - '0';
        return x;
    }
    inline int xint() {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32)
            c = xchar();
        if (c == '-')
            s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar())
            x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s) {
        int c = xchar();
        while (c <= 32)
            c = xchar();
        for (; c > 32; c = xchar())
            *s++ = c;
        *s = 0;
    }
    inline void wchar(int x) {
        if (wpos == S)
            fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(int x) {
        if (x < 0)
            wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n)
            s[n++] = '0' + x % 10, x /= 10;
        while (n--)
            wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s)
            wchar(*s++);
    }
    ~FastIO() {
        if (wpos)
            fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
struct Node {
    int u, p, k, d, id;
    Node() {

    }
    Node(int _u, int _p, int _k, int _d, int _id) {
        u = _u, p = _p, k = _k, d = _d, id = _id;
    }
    void out() {
        printf("u = %d, p = %d, k = %d, d = %d, id = %d\n", u, p, k, d, id);
    }
    bool operator<(const Node &nd) const {
        if (k != nd.k)
            return k < nd.k;
        return d < nd.d;
    }
} q[N * 2];
struct Edge {
    int t, nxt;
    Edge() {

    }
    Edge(int _t, int _nxt) {
        t = _t, nxt = _nxt;
    }
} e[N * 2];
int n, m, B, a[N], ans[N], et, head[N];
int tot, s[N], g[N], w[N], rec[N], dep[N], par[N], top[N], siz[N];
void addEdge(int s, int t) {
    e[et] = Edge(t, head[s]), head[s] = et++;
    e[et] = Edge(s, head[t]), head[t] = et++;
}
void dfs(int u, int p) {
    s[u] = -1, par[u] = p, siz[u] = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].t;
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
        siz[u] += siz[v];
        if (s[u] == -1 || siz[v] > siz[s[u]])
            s[u] = v;
    }
}
void DFS(int u, int rt, int p) {
    rec[w[u] = ++tot] = u, top[u] = rt;
    if (~s[u])
        DFS(s[u], rt, u);
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].t;
        if (v == p || v == s[u])
            continue;
        DFS(v, v, u);
    }
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = par[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
int up(int u, int k) {
    while (~u && k > 0) {
        if (dep[u] - dep[top[u]] < k) {
            if (top[u] == 1)
                return -1;
            k -= dep[u] - dep[top[u]] + 1;
            u = par[top[u]];
        } else {
            u = rec[w[u] - k];
            break;
        }
    }
    return u;
}
int calc(int u, int p, int k, int dd) {
    if (dd < 0)
        return 0;
    int v = up(u, dd), ret = 0;
    while (~v && dep[v] >= dep[p]) {
        ret = max(ret, a[v]);
        v = up(v, k);
    }
    return ret;
}
int pos[N], val[N * 4];
void build(int t, int l, int r) {
    if (l == r) {
        pos[l] = t;
        return;
    }
    int mid = (l + r) >> 1;
    build(t << 1, l, mid), build(t << 1 | 1, mid + 1, r);
}
inline void upd(int j, int v) {
    j = pos[j];
    val[j] = v;
    int i = j >> 1;
    while (i > 0) {
        val[i] = max(val[i << 1], val[i << 1 | 1]);
        j = i;
        i = j >> 1;
    }
}
inline int qryMax(int t, int l, int r, int a, int b) {
    if (b < l || r < a)
        return 0;
    if (a <= l && r <= b)
        return val[t];
    int mid = (l + r) >> 1;
    return max(qryMax(t << 1, l, mid, a, b),
            qryMax(t << 1 | 1, mid + 1, r, a, b));
}
inline int calc2(int u, int v) {
    int tu = top[u], tv = top[v], ret = 0;
    while (tu != tv) {
        if (dep[tu] < dep[tv])
            swap(u, v), swap(tu, tv);
        ret = max(ret, qryMax(1, 1, n, w[tu], w[u]));
        tu = top[u = par[tu]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ret = max(ret, qryMax(1, 1, n, w[u], w[v]));
    return ret;
}
int main() {
//    freopen("data.in", "r", stdin);
    int T;
    T = io.xuint();
    rep(cas, 0, T)
    {
        n = io.xuint();
        m = io.xuint();
        et = 0, B = min(50, (int) sqrt(n));
        rep(i, 1, n + 1)
            a[i] = io.xuint(), head[i] = -1;
        rep(i, 1, n)
        {
            int u, v;
            u = io.xuint();
            v = io.xuint();
            addEdge(u, v);
        }
        dep[1] = 0, dfs(1, -1);
        tot = 0, DFS(1, 1, -1);
        tot = 0;
        rep(_m, 0, m)
        {
            int u, v, k, p;
            u = io.xuint();
            v = io.xuint();
            k = io.xuint();
            p = lca(u, v);
            if (k >= B) {
                ans[_m] = max(calc(u, p, k, k - 1),
                        calc(v, p, k, (dep[u] + dep[v] + 1 - 2 * dep[p]) % k));
            } else {
                ans[_m] = 0;
                q[tot++] = Node(u, p, k, (dep[u] + 1) % k, _m);
                q[tot++] = Node(v, p, k,
                        ((2 * dep[p] - dep[u] - 1) % k + k) % k, _m);
            }
        }
        sort(q, q + tot), build(1, 1, n);
        for (int i = 0, j, k; i < tot; i = j) {
            j = i + 1;
            while (j < tot && q[j].k == q[i].k)
                ++j;
            k = q[i].k;
            rep(I, 0, k)
                siz[I] = 0;
            rep(u, 1, n + 1)
                ++siz[dep[u] % k];
            s[0] = 1, g[0] = siz[0];
            rep(I, 1, k)
            {
                s[I] = siz[I - 1] + 1;
                siz[I] += siz[I - 1];
                g[I] = siz[I];
            }
            rep(u, 1, n + 1)
                rec[siz[dep[u] % k]--] = u;
            int l = i, r, d;
            while (l < j) {
                r = l + 1, d = q[l].d;
                while (r < j && q[r].d == d)
                    ++r;
                rep(I, s[d], g[d] + 1)
                    upd(w[rec[I]], a[rec[I]]);
                while (l < r) {
                    ans[q[l].id] = max(ans[q[l].id], calc2(q[l].u, q[l].p));
                    ++l;
                }
                rep(I, s[d], g[d] + 1)
                    upd(w[rec[I]], 0);
            }
        }
        printf("Case #%d:\n", cas + 1);
        rep(i, 0, m)
            printf("%d\n", ans[i]);
    }
    return 0;
}