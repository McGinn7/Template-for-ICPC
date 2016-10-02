#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 44;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int n, m, a[N];
int b[N], s[N];
//void gauss() {
//	int i = 0, x = 19;
//	for (; i < n && x >= 0; ++i, --x) {
//		int r = i;
//		while (r < n && !(a[r] >> x & 1))
//			++r;
//		if (r >= n) {
//			--i;
//			continue;
//		}
//		if (r != i)
//			swap(a[i], a[r]);
//		rep(j, 0, n)
//			if (i != j && (a[j] >> x & 1))
//				a[j] ^= a[i];
//	}
//}
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
int calc(int x) {
	for (int i = 0; x > 0; ++i)
		if (x >> i & 1)
			return i;
	return 0;
}
ll kpow(ll a, ll b) {
	ll r = 1;
	while (b > 0) {
		if (b & 1)
			r = r * a;
		a = a * a, b >>= 1;
	}
	return r;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d%d", &n, &m);
		rep(i, 0, n)
			scanf("%d", a + i);
		gauss();
		memset(b, 0, sizeof(b));
		memset(s, 0, sizeof(s));
		vector<int> V;
		rep(i, 0, n)
			if (a[i])
				V.pb(a[i]);
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()), V.end());
		rep(i, 0, sz(V))
			for (int j = 19; j >= 0; --j)
				if (V[i] >> j & 1) {
					b[j] = V[i];
					break;
				}
		rep(i, 0, 20)
			s[i] = (b[i] > 0) + (i > 0 ? s[i - 1] : 0);
		ll st = 0, ans = 0;
		for (int i = 19; i >= 0; --i)
			if (m >> i & 1) {
				if (!(st >> i & 1) && !b[i])
					break;
				if (!(st >> i & 1))
					st ^= b[i];
			} else {
				if (b[i]) {
					if (st >> i & 1)
						st ^= b[i];
					ans += kpow(2, s[i] - 1);
				} else {
					if (st >> i & 1) {
						ans += kpow(2, s[i]) - 1;
						break;
					}
				}
			}
		ans += st >= m;
		ans *= kpow(2, n - sz(V));
		printf("Case #%d: %I64d\n", cas + 1, ans);
	}
	return 0;
}
/*
 5
 3 0
 1 2 3
 3 1
 1 2 3
 3 2
 1 2 3
 3 3
 1 2 3
 3 4
 1 2 3
 */
