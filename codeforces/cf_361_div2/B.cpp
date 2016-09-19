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
#define sqr(x) ((ll)(x)*(x))
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
const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
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
const int d[] = { -1, 1 };
int n, a[N], f[N];
queue<int> que;
int main() {
	scanf("%d", &n);
	rep(i, 0, n)
		scanf("%d", &a[i]), --a[i];
	rep(i, 0, n)
		f[i] = -1;
	f[0] = 0, que.push(0);
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		if (!~f[a[x]]) {
			f[a[x]] = f[x] + 1;
			que.push(a[x]);
		}
		rep(i, 0, 2)
			if (0 <= x + d[i] && x + d[i] < n && !~f[x + d[i]]) {
				f[x + d[i]] = f[x] + 1;
				que.push(x + d[i]);
			}
	}
	rep(i, 0, n)
	{
		if (i)
			putchar(' ');
		printf("%d", f[i]);
	}
	return 0;
}