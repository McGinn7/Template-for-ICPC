#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
 
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = ~0ULL >> 1;
const int N = 4e5 + 7;
const int INF = 2e8 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
namespace HPI {
struct Node {
    double x, y;
    Node() {
    }
    Node(double _x, double _y) {
        x = _x, y = _y;
    }
} p[N << 1];
struct Seg {
    double r;
    Node s, e;
    void getr() {
        r = atan2(e.y - s.y, e.x - s.x);
    }
} seg[N], Q[N];
int n;
void init() {
    n = 0;
}
int sign(double x) {
    if (fabs(x) < EPS)
        return 0;
    return x > 0 ? 1 : -1;
}
void addSeg(double x0, double y0, double x1, double y1) {
    seg[n].s = Node(x0, y0), seg[n].e = Node(x1, y1);
    seg[n++].getr();
}
double xmul(Node o, Node a, Node b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
Node getIns(Seg s1, Seg s2) {
    double u = xmul(s1.s, s1.e, s2.s), v = xmul(s1.e, s1.s, s2.e);
    return Node((s2.s.x * v + s2.e.x * u) / (u + v),
            (s2.s.y * v + s2.e.y * u) / (u + v));
}
bool cmp(Seg s1, Seg s2) {
    if (sign(s1.r - s2.r) > 0)
        return true;
    if (sign(s1.r - s2.r) == 0 && sign(xmul(s2.s, s2.e, s1.e)) >= 0)
        return true;
    return false;
}
double getArea(Node *p, int n) {
    double area = 0;
    rep(i, 1, n - 1)
        area += xmul(p[0], p[i], p[i + 1]);
    return fabs(area) * 0.5;
}
double run() {
    sort(seg, seg + n, cmp);
    int tmp = 1;
    rep(i, 1, n)
        if (sign(seg[i].r - seg[tmp - 1].r))
            seg[tmp++] = seg[i];
    n = tmp, Q[0] = seg[0], Q[1] = seg[1];
    int h = 0, r = 1;
    rep(i, 2, n)
    {
        while (h < r
                && sign(xmul(seg[i].s, seg[i].e, getIns(Q[r], Q[r - 1]))) < 0)
            --r;
        while (h < r
                && sign(xmul(seg[i].s, seg[i].e, getIns(Q[h], Q[h + 1]))) < 0)
            ++h;
        Q[++r] = seg[i];
    }
    while (h < r && sign(xmul(Q[h].s, Q[h].e, getIns(Q[r], Q[r - 1]))) < 0)
        --r;
    while (h < r && sign(xmul(Q[r].s, Q[r].e, getIns(Q[h], Q[h + 1]))) < 0)
        ++h;
    if (h == r)
        return 0;
    int m = 0;
    rep(i, h, r)
        p[m++] = getIns(Q[i], Q[i + 1]);
    if (r > h + 1)
        p[m++] = getIns(Q[h], Q[r]);
    return getArea(p, m);
}
}
 
int n, m, T;
vector<pii> path;
vector<pair<int, pii> > e[20];
void dfs(int u, int st, int C, int D) {
    if (u == n - 1) {
        path.pb(mp(C, D));
        return;
    }
    rep(i, 0, sz(e[u]))
    {
        int v = e[u][i].first;
        if (st >> v & 1)
            continue;
        dfs(v, st | (1 << v), C + e[u][i].second.first,
                D + e[u][i].second.second);
    }
}
int main() {
    while (scanf("%d%d%d", &n, &m, &T) == 3) {
        rep(i, 0, n)
            e[i].clear();
        rep(i, 0, m)
        {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            --a, --b;
            e[a].pb(mp(b, mp(c, d)));
        }
        path.clear();
        dfs(0, 1, 0, 0);
        HPI::init();
        HPI::addSeg(0, INF, 0, 0);
        HPI::addSeg(0, 0, T, 0);
        HPI::addSeg(T, 0, T, INF);
        rep(i, 0, sz(path))
            if (path[i].first) {
                double y1, y2;
                y1 = 1.0 * path[i].first * T + path[i].second;
                y2 = path[i].second;
                HPI::addSeg(T, y1, 0, y2);
            }
        double ans = HPI::run();
        printf("%.8lf\n", ans / T);
    }
    return 0;
}