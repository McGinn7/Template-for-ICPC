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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, a[N], f[N];
vector<int> d[2];
bool check(int l, int r, int D) {
    rep(i, l, r + 1)
        if (a[i] && D != a[i] - i)
            return false;
    return true;
}
int calc(int x, int D) {
    int ret = 0;
    while (1 <= x && x <= n && !a[x])
        ++ret, x += D;
    return ret;
}
ll solve() {
    int c = 0, x = -1;
    rep(i, 1, n + 1)
        if (a[i] && abs(i - a[i]) > 1)
            ++c, x = i;
    if (c > 1)
        return 0;
    if (sz(d[0]) == 1 && sz(d[1]) == 1)
        c = 1, x = d[0][0];
    if (c == 1) {
        int l = min(x, a[x]), r = max(x, a[x]);
        if (f[l - 1] != f[0] || f[n] != f[r])
            return 0;
        return a[x] < x ? check(a[x], x - 1, 1) : check(x + 1, a[x], -1);
    }
    if (!d[0].empty()) { // i -> i + 1
        int l = d[0].front(), r = d[0].back();
        if (f[l - 1] != f[0] || f[r] != f[n] || !check(l, r, -1))
            return 0;
        ll x = calc(l - 1, -1), y = calc(r + 1, 1);
        return x * y + x;
    }
    if (!d[1].empty()) { // i - 1 <- i
        int l = d[1].front(), r = d[1].back();
        if (f[l - 1] != f[0] || f[r] != f[n] || !check(l, r, 1))
            return 0;
        ll x = calc(l - 1, -1), y = calc(r + 1, 1);
        return x * y + y;
    }
    // not move
    ll ret = 0;
    for (int i = 1, j; i <= n; i = j)
        if (!a[i]) {
            j = i + 1;
            while (j <= n && !a[j])
                ++j;
            ret += 1ll * (j - i - 1) * (j - i - 1);
        } else {
            j = i + 1;
        }
    return ret;
}
int main() {
//  freopen("data.in", "r", stdin);
    while (~scanf("%d", &n)) {
        d[0].clear(), d[1].clear();
        rep(i, 1, n + 1)
            scanf("%d", &a[i]);
        rep(i, 1, n + 1)
        {
            f[i] = f[i - 1];
            if (a[i]) {
                if (i != a[i])
                    ++f[i];
                if (a[i] == i - 1)
                    d[0].pb(i);
                if (a[i] == i + 1)
                    d[1].pb(i);
            }
        }
        cout << solve() << endl;
    }
    return 0;
}