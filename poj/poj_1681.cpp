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
int n, a[20], b[20], st[1 << 15], cnt[1 << 15];
char str[20];
void init(int n) {
	rep(mask, 1, 1 << n)
	{
		st[mask] = 0, cnt[mask] = 1 + cnt[mask ^ (mask & -mask)];
		rep(i, 0, n)
			if (mask >> i & 1) {
				st[mask] ^= 1 << i;
				if (i)
					st[mask] ^= 1 << (i - 1);
				if (i + 1 < n)
					st[mask] ^= 1 << (i + 1);
			}
	}
}
int solve(int a[], int msk) {
	int ret = cnt[msk];
	a[0] ^= st[msk], a[1] ^= msk;
	rep(i, 1, n)
	{
		ret += cnt[a[i - 1]];
		a[i] ^= st[a[i - 1]], a[i + 1] ^= a[i - 1];
	}
	if (a[n - 1] != 0)
		return INF;
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		init(n);
		rep(i, 0, n)
		{
			a[i] = 0, scanf(" %s", str);
			rep(j, 0, n)
				a[i] = (a[i] << 1) | (str[j] == 'w');
		}
		if (n == 1) {
			printf("%d\n", a[0]);
			continue;
		}
		int ans = INF;
		rep(mask, 0, 1 << n)
		{
			rep(i, 0, n)
				b[i] = a[i];
			ans = min(ans, solve(b, mask));
		}
		ans < INF ? printf("%d\n", ans) : puts("inf");
	}
	return 0;
}