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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
int n;
ll a[N];
void gauss(int n) {
	int i = 0, c = 60;
	for (; i < n && c >= 0; ++i, --c) {
		int r = i;
		while (r < n && !(a[r] >> c & 1))
			++r;
		if (r >= n) {
			--i;
			continue;
		}
		if (r != i)
			swap(a[r], a[i]);
		rep(j, 0, n)
			if (i != j && (a[j] >> c & 1))
				a[j] ^= a[i];
	}
}
int main() {
	scanf("%d", &n);
	rep(i, 0, n)
		scanf("%I64d", &a[i]);
	gauss(n);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	ll ans = 0;
	rep(i, 0, n)
		ans ^= a[i];
	printf("%I64d", ans);
	return 0;
}