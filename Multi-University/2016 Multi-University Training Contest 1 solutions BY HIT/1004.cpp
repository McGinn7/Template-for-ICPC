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
const ul BASE = 29;
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
int n, a[N], lg[N], g[N][20];
map<int, ll> M;
int get(int l, int r) {
    int k = lg[r - l + 1];
    return __gcd(g[l][k], g[r - (1 << k) + 1][k]);
}
int main() {
    lg[1] = 0;
    rep(i, 2, N)
        lg[i] = lg[i - 1] + (i == (i & -i));
    int T;
    scanf("%d", &T);
    rep(cas, 0, T)
    {
        scanf("%d", &n);
        rep(i, 0, n)
            scanf("%d", &a[i]), g[i][0] = a[i];
        for (int j = 1; (1 << j) - 1 < n; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                g[i][j] = __gcd(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
            }
        }
        M.clear();
        rep(i, 0, n)
        {
            int p = i;
            while (p < n) {
                int l = p, r = n - 1, G = get(i, p);
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    get(i, mid) == G ? l = mid : r = mid;
                }
                int q = (get(i, r) == G ? r : l);
                if (M.find(G) == M.end())
                    M[G] = 0;
                M[G] += q - p + 1;
                p = q + 1;
            }
        }
        printf("Case #%d:\n", cas + 1);
        int m;
        scanf("%d", &m);
        rep(i, 0, m)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            --l, --r;
            int g = get(l, r);
            printf("%d %I64d\n", g, M[g]);
        }
    }
    return 0;
}