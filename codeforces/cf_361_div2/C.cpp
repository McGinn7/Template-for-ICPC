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
const ul BASE = 33;
const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.);
const double EPS = 1e-8;
ll kpow(ll a, ll b) {
	ll ret = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1)
			ret = ret * a;
	return ret;
}
//--------------head--------------
ll m;
ll check(ll n) {
	ll ret = 0;
	for (ll k = 2; k * k * k <= n; ++k)
		ret += n / (k * k * k);
	return ret;
}
int main() {
	scanf("%I64d", &m);
	ll l = 0, r = LINF;
	while (l + 1 < r) {
		ll mid = (l + r) >> 1;
		check(mid) >= m ? r = mid : l = mid;
	}
	ll n = -1;
	if (check(l) == m)
		n = l;
	else if (check(r) == m)
		n = r;
	printf("%I64d\n", n);
	return 0;
}