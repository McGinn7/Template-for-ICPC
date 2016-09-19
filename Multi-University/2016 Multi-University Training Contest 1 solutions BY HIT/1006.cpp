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
const int N = 1e7 + 7;
const int P = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1000000007;
const double Pi = acos(-1.);
const double EPS = 1e-10;
ll kpow(ll a, ll b, ll mod) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            ret = ret * a % mod;
    return ret;
}
//--------------head-------------
int n, m, p, k, phi[N], sum[N];
vi prime;
map<pii, int> F;
map<int, int> S;
void inc(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}
void init() {
    for (int i = 1; i < N; ++i)
        phi[i] = i >> (1 - (i & 1));
    prime.pb(2);
    for (int i = 3; i < N; i += 2)
        if (phi[i] == i) {
            prime.pb(i);
            for (int j = i; j < N; j += i)
                phi[j] = phi[j] / i * (i - 1);
        }
    int cnt = 0;
    rep(i, 1, N)
        inc(cnt, phi[i]), sum[i] = cnt;
}
vi fac;
int f(int t, int n, int m) {
    if (!m || n == 1)
        return sum[m];
    if (F.find(mp(n, m)) != F.end())
        return F[mp(n, m)];
    int ret = 0;
    inc(ret, 1ll * phi[fac[t]] * f(t + 1, n / fac[t], m) % MOD);
    inc(ret, f(t, n, m / fac[t]));
    return F[mp(n, m)] = ret;
}
void _fac(int n, vi &a) {
    a.clear();
    rep(i, 0, sz(prime))
        if (1ll * prime[i] * prime[i] <= n) {
            if (n % prime[i] == 0)
                a.pb(prime[i]), n /= prime[i];
        } else
            break;
    if (n > 1)
        a.pb(n);
}
int solve(int p) {
    if (k % p == 0)
        return 0;
    return kpow(k, phi[p] + solve(phi[p]), p);
}
int main() {
    init();
    while (~scanf("%d%d%d", &n, &m, &p)) {
        F.clear(), S.clear();
        _fac(n, fac);
        k = f(0, n, m);
        printf("%d\n", solve(p));
    }
    return 0;
}