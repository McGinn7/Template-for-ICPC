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
const int N = 3e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1000000007;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
bool vis[N];
vector<int> pri;
void prime() {
	memset(vis, false, sizeof(vis));
	for (int x = 2; x < N; ++x)
		if (!vis[x]) {
			pri.pb(x);
			for (ll y = 1ll * x * x; y < N; y += x)
				vis[y] = true;
		}
}
int n, sum[N];
bool check(int p, int x) {
	int mx = 3 * n + 18;
//	sum[1] = 2 * 1 * p + (1 * (1 + 1) / 2 * x) % p;
	rep(i, 1, n + 1)
	{
		sum[i] = 2 * i * p + (1ll * i * (i + 1) / 2 * x) % p;
		if (sum[i] - sum[i - 1] >= mx)
			return false;
	}
	return true;
}
void chkans() {
	vector<int> V;
	rep(i, 0, n)
		rep(j, i + 1, n + 1)
			V.pb(sum[j] - sum[i]);
	sort(V.begin(), V.end());
	bool flag = true;
	rep(i, 1, sz(V))
		if (V[i - 1] == V[i]) {
			flag = false;
			break;
		}
	puts(flag ? "Yes" : "No");
}
int main() {
	prime();
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		scanf("%d", &n);
		int p = pri[upper_bound(pri.begin(), pri.end(), n) - pri.begin()];
//		printf("p = %d\n", p);
		rep(x, 1, p)
			if (check(p, x)) {
//				printf("x = %d\n", x);
				break;
			}
		rep(i, 1, n + 1)
		{
			if (i - 1)
				putchar(' ');
			printf("%d", sum[i] - sum[i - 1]);
		}
		puts("");
//		chkans();
	}
	return 0;
}