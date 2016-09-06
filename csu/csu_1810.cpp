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
const ll LINF = ~0ULL >> 1;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, m, p[N], pre[N], suf[N], sum[N], f[N];
char d[N];
void inc(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}
ll kpow(ll a, ll b) {
    ll r = 1;
    while (b > 0) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return r;
}
ll F(int x) {
    if (~f[x])
        return f[x];
    if (!x)
        return f[x] = 0;
    if (x == 1)
        return f[x] = 1;
    return f[x] = 1ll * x * (x + 1) % MOD * kpow(2, MOD - 2) % MOD;
}
int main() {
//  freopen("data.in", "r", stdin);
    p[0] = 1;
    rep(i, 1, N)
        p[i] = 1ll * p[i - 1] * 10 % MOD;
    memset(f, -1, sizeof(f));
    while (~scanf("%d", &n)) {
        scanf(" %s", d + 1);
        sum[0] = 0, pre[0] = 0, suf[n + 1] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1];
            inc(sum[i], d[i] - '0');
            pre[i] = pre[i - 1];
            inc(pre[i], i * (d[i] - '0'));
            suf[n - i + 1] = suf[n - i + 2];
            inc(suf[n - i + 1], i * (d[n - i + 1] - '0'));
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int cnt = 0, L = min(i, n - i + 1);
            inc(cnt, pre[L]);
            if (L != n - L + 1)
                inc(cnt, suf[n - L + 1]);
            else if (n - L + 2 <= n)
                inc(cnt, suf[n - L + 2]);
            if (n - L > L)
                inc(cnt, 1ll * L * (sum[n - L] - sum[L] + MOD) % MOD);
            inc(cnt, (F(i - 1) + F(n - i)) % MOD * (d[i] - '0') % MOD);
//          printf("L = %d, cnt[%d] = %d\n", L, i, cnt);
            inc(ans, 1ll * cnt * p[n - i] % MOD);
        }
        printf("%d\n", ans);
    }
    return 0;
}