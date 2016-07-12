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
const int N = 3e8 + 7;
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
bitset<N> p;
int d[] = { 1, 0, 3, 2 };
void prime(int n) {
	p[1] = 1;
	for (int i = 3; i * i < n; i += 2)
		if (!p[i])
			for (int j = i * i; j < n; j += (i << 1))
				p[j] = 1;
}
int main() {
	int l, r, ans = 0;
	scanf("%d%d", &l, &r);
	prime(r + 1);
	for (int i = l + d[l % 4]; i <= r; i += 4)
		ans += p[i] ^ 1;
	ans += (l <= 2 && 2 <= r);
	printf("%d", ans);
	return 0;
}
