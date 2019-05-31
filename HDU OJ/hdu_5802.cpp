#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 9e5 + 7;
const int MOD = 1e9 + 7;
//--------head---------
ll solve(ll x, ll y) {
    if (x <= y)
        return y - x;
    ll sum = 0, stop = 0, ret = MOD;
    while (x > y) {
        ll k = 0;
        while (x + 1 - (1ll << (k + 1)) >= y)
            ++k;
        ll nx = x + 1 - (1ll << (k + 1));
        nx = max(0ll, nx);
        ret = min(ret, sum + k + 1 + max(0ll, y - nx - stop));
        x -= (1ll << k) - 1;
        ++stop, sum += 1 + k;
    }
    ret = min(ret, sum - 1);
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        ll p, q;
//        cin >> p >> q;
//        cout << solve(p, q) << endl;
        scanf("%I64d%I64d", &p, &q);
        printf("%I64d\n", solve(p, q));
    }
    return 0;
}