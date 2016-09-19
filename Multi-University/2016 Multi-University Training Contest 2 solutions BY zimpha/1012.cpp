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
const int N = 1e5 + 7;
const int M = 5e3 + 7;
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
int n, m;
char s[N], p[M], ans[N];
bitset<M> L[26], P[26], R[26];
bitset<M> dp[3], tmp[3];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d %s%s", &n, &m, s, p);
		rep(i, 0, 26)
			P[i].reset();
		rep(i, 0, m)
			P[p[i] - 'a'][i] = 1;
		rep(i, 0, 26)
			L[i] = P[i] << 1, R[i] = P[i] >> 1;
		rep(i, 0, n)
			ans[i] = '0';
		rep(i, 0, 3)
			dp[i].reset();
		int x;
		rep(i, 0, n)
		{
			x = s[i] - 'a';
			tmp[0] = dp[2] << 1;
			tmp[1] = (dp[0] << 1 | dp[1] << 1);
			tmp[2] = tmp[1];
			rep(j, 0, 3)
				tmp[j][0] = 1;
			dp[0] = tmp[0] & L[x];
			dp[1] = tmp[1] & P[x];
			dp[2] = tmp[2] & R[x];
			if (dp[0][m - 1] || dp[1][m - 1])
				ans[i - m + 1] = '1';
		}
		ans[n] = '\0';
		puts(ans);
	}
	return 0;
}
