#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = 1e16 + 7;
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int kpow(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b & 1)
			r *= a;
		a = a * a, b >>= 1;
	}
	return r;
}
const int x[] = { 2, 3, 7 };
const int U[] = { 5, 2, 1 };
int n, m, a[3];
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		ll ans = 0;
		for (a[0] = 0; a[0] <= 5; ++a[0])
			for (a[1] = 0; a[1] <= 2; ++a[1])
				for (a[2] = 0; a[2] <= 1; ++a[2]) {
					int A = 1, B = 2016, cnt;
					rep(i, 0, 3)
						A *= kpow(x[i], a[i]), B /= kpow(x[i], a[i]);
					cnt = 0;
					rep(mask, 0, 8)
					{
						int pA = 1;
						bool flag = true;
						rep(i, 0, 3)
							if (a[i] + (mask >> i & 1) > U[i]) {
								flag = false;
								break;
							} else {
								pA *= kpow(x[i], a[i] + (mask >> i & 1));
							}
						if (flag)
							cnt += ((__builtin_popcount(mask) & 1) ?
									-n / pA : n / pA);
					}
					ans += 1ll * cnt * (m / B);
				}
		cout << ans << endl;
	}
	return 0;
}
