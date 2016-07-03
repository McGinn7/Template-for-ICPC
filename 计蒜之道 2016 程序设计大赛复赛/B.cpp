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
#define sqr(x) ((x)*(x))
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
const int MOD = 2e9 + 7;
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
int a, b, c;
bool check(int A, int B, int C, int sum) {
	int mx = max(A, max(B, C)), sx = A + B + C - mx;
	mx = min(mx, sx + 1);
	return mx + sx >= sum;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d%d", &a, &b, &c);
		int ans = 0;
		rep(i, 1, b + 1)
			if (check(a - i, b - i, c, i))
				ans = i;
		printf("%d\n", ans);
	}
	return 0;
}
