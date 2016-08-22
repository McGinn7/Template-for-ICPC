#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<assert.h>
#include<sstream>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e18 + 7;
const int N = 1e4 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
int n, q;
ll a[N];
void gauss() {
	int i = 0, x = 60;
	for (; i < n && x >= 0; ++i, --x) {
		int r = i;
		while (r < n && !(a[r] >> x & 1))
			++r;
		if (r >= n) {
			--i;
			continue;
		}
		if (r != i)
			swap(a[r], a[i]);
		rep(j, 0, n)
			if (i != j && (a[j] >> x & 1))
				a[j] ^= a[i];
	}
}
ll solve(ll k) {
	k -= a[0] == 0;
	ll ret = 0;
	for (int i = a[0] == 0; i < n && k; ++i, k >>= 1)
		if (k & 1)
			ret ^= a[i];
	if (k)
		return -1;
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		rep(i, 0, n)
			scanf("%I64d", &a[i]);
		gauss();
		sort(a, a + n);
		n = unique(a, a + n) - a;
		printf("Case #%d:\n", cas + 1);
		scanf("%d", &q);
		rep(_q, 0, q)
		{
			ll k;
			scanf("%I64d", &k);
			printf("%I64d\n", solve(k));
		}
	}
	return 0;
}