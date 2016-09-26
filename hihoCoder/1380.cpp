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
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 4782969 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int n, pw[20], f[N], mc[N], cnt[N];
char s[(1 << 14) + 7];
inline void _min(int &x, int y) {
	if (x > y)
		x = y;
}
int main() {
//	n = 14, memset(s, '0', sizeof(s));
	scanf("%d %s", &n, s);
	pw[0] = 1;
	rep(i, 1, n + 1)
		pw[i] = 3 * pw[i - 1];
	rep(mask, 0, 1 << n) {
		int x = 0;
		rep(i, 0, n)
			x = (mask >> i & 1) * pw[i] + x;
		f[x] |= 1 << (s[mask] - '0');
	}
	rep(mask, 0, pw[n]) {
		cnt[mask] = 0, mc[mask] = n;
		rep(i, 0, n) {
			int x = mask / pw[i] % 3;
			if (x == 2) {
				f[mask] |= f[mask - x * pw[i]];
				f[mask] |= f[mask - x * pw[i] + pw[i]];
			} else {
				++cnt[mask];
			}
		}
	}
	for (int mask = pw[n] - 1; mask >= 0; --mask) {
		if (f[mask] != 3)
			_min(mc[mask], cnt[mask]);
		rep(i, 0, n) {
			int x = mask / pw[i] % 3;
			if (x == 2) {
				_min(mc[mask - x * pw[i]], mc[mask]);
				_min(mc[mask - x * pw[i] + pw[i]], mc[mask]);
			}
		}
	}
	rep(mask, 0, 1 << n) {
		int x = 0;
		rep(i, 0, n)
			x = (mask >> i & 1) * pw[i] + x;
		if (mask)
			putchar(' ');
		printf("%d", mc[x]);
	}
	return 0;
}
