#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
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
const ll LINF = 1e10 + 7;
const int N = 20;
const int INF = 1e9 + 7;
const int MOD = 1000000007;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, lnk[N];
bool ind[1 << 18];
unsigned int f[1 << 18];
unsigned int kpow(unsigned int a, int b) {
	unsigned int r = 1;
	while (b > 0) {
		if (b & 1)
			r *= a;
		a = a * a, b >>= 1;
	}
	return r;
}
char str[N];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		rep(i, 0, n)
		{
			lnk[i] = 0, scanf(" %s", str);
			rep(j, 0, n)
				lnk[i] = (lnk[i] << 1) | (str[n - 1 - j] - '0');
		}
		memset(ind, false, sizeof(ind[0]) * (1 << n));
		f[0] = 0, ind[0] = true;
		unsigned int ans = 0;
		rep(mask, 1, 1 << n)
		{
			if (ind[mask ^ (mask & -mask)]) {
				int i = 0;
				for (i = 0; i < n; ++i)
					if ((mask & -mask) >> i & 1)
						break;
				ind[mask] = !(mask & lnk[i]);
			}
			f[mask] = __builtin_popcount(mask);
			for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
				if (ind[sub])
					f[mask] = min(f[mask], f[mask ^ sub] + 1);
			ans += f[mask] * kpow(233, mask);
		}
		printf("%u\n", ans);
	}
	return 0;
}
/*
 1
 18
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111
111111111111111111

 */