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
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-9;
ll kpow(ll a, ll b, ll mod) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            ret = ret * a % mod;
    return ret;
}
//--------------head-------------
int n, m, a[N], L[2], R[2];
struct Node {
    ll x, y;
    Node() {

    }
    Node(ll _x, ll _y) {
        x = _x, y = _y;
        ll g = __gcd(x, y);
        if (g)
            x /= g, y /= g;
    }
    bool operator<(const Node &p) const {
        return x * p.y < y * p.x;
    }
};
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T)
    {
        scanf("%d%d", &n, &m);
        rep(i, 0, n)
            a[i] = -1;
        rep(i, 0, m)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[--x] = y;
        }
        int sum = 0, last = 0;
        for (int i = n - 1; i > 1; --i) {
            if (~a[i])
                last = a[i];
            a[i] = last, sum += last;
        }
        Node ans(0, 1);
        rep(i, 0, 2)
            if (~a[i])
                L[i] = R[i] = a[i];
            else
                L[i] = last, R[i] = 100;
        rep(j, L[1], R[1] + 1)
            rep(i, max(j, L[0]), R[0] + 1)
                if (sum + i + j > 0 && ans < Node(i + j, sum + i + j))
                    ans = Node(i + j, sum + i + j);
        printf("%I64d/%I64d\n", ans.x, ans.y);
    }
    return 0;
}