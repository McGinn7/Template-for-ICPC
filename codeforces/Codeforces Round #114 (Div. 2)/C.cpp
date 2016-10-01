#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iomanip>
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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, a, d, t[N], v[N], f[N];
double time(ll v, ll t) {
	double ret;
	if (v * v  >= 2ll * a * d) {
		ret = sqrt(2.0 * d / a);
	} else {
		double dt = 1.0 * v / a;
		ret = dt + 1.0 * (d - (v * v) / (2.0 * a)) / v;
	}
	return t + ret;
}
int main() {
//	ios::sync_with_stdio(false);
//	cin >> n >> a >> d;
	scanf("%d%d%d", &n, &a, &d);
	rep(i, 0, n)
		scanf("%d%d", &t[i], &v[i]);
	double last = 0;
	rep(i, 0, n) {	
		double arr = time(v[i], t[i]);
		last = max(last, arr);
		printf("%.10lf\n", last);
	}
	return 0;
}