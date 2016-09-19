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
const ll LINF = 1e17 + 7;
const ul BASE = 33;
const int N = 1e5 + 7;
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
int n;
pii p[11];
char str[11];
pii calc(int x) {
	if (!x)
		return mp(3, 1);
	--x;
	return mp(x / 3, x % 3);
}
bool check(int dx, int dy) {
	rep(i, 0, n)
	{
		int x = p[i].fi + dx, y = p[i].se + dy;
		bool flag = false;
		if (0 <= x && x < 3 && 0 <= y && y < 3)
			flag = true;
		if (x == 3 && y == 1)
			flag = true;
		if (!flag)
			return false;
	}
	return true;
}
int main() {
	scanf("%d", &n);
	scanf(" %s", str);
	rep(i, 0, n)
		p[i] = calc(str[i] - '0');
	int cnt = 0;
	rep(dx, -3, 4)
		rep(dy, -3, 4)
			if (check(dx, dy))
				++cnt;
	puts(cnt == 1 ? "YES" : "NO");
	return 0;
}
