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
const ul BASE = 29;
const int N = 2e3 + 7;
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
char t[N], be[N], en[N];
bool ib[N], ie[N];
int tl, bl, el;
ul b, e, f[N], base[N];
vector<ul> vec;
ul get(int l, int r) {
	return f[r] - (l ? f[l - 1] * base[r - l + 1] : 0);
}
ul calc(char str[]) {
	ul ret = 0;
	int len = strlen(str);
	rep(i, 0, len)
		ret = ret * BASE + str[i] - 'a' + 1;
	return ret;
}
int main() {
	base[0] = 1;
	rep(i, 1, N)
		base[i] = base[i - 1] * BASE;
	scanf(" %s %s %s", t, be, en);
	tl = strlen(t), bl = strlen(be), el = strlen(en);
	f[0] = t[0] - 'a' + 1;
	for (int i = 1; i < tl; ++i)
		f[i] = f[i - 1] * BASE + t[i] - 'a' + 1;
	rep(i, 0, tl)
		ib[i] = ie[i] = false;
	b = calc(be), e = calc(en);
	for (int i = 0, I = tl - bl; i <= I; ++i)
		if (get(i, i + bl - 1) == b)
			ib[i] = true;
	for (int i = tl - 1, I = el - 1; i >= I; --i)
		if (get(i - el + 1, i) == e)
			ie[i] = true;
	rep(i, 0, tl)
		rep(j, i + max(bl, el) - 1, tl)
			if (ib[i] && ie[j])
				vec.pb(get(i, j));
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
	printf("%d", sz(vec));
	return 0;
}
