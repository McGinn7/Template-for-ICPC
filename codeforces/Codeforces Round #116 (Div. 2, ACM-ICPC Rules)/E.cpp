
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<sstream>
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
int n, m, k;
vector<int> vec[N];
int solve(const vector<int> &p) {
	if (!sz(p))
		return 0;
	int l = 0, d = 0, ret = 1;
	rep(i, 1, sz(p)) {
		while (d + p[i] - p[i - 1] - 1> k) {
			d -= p[l + 1] - p[l] - 1; 
			++l;
		}
		d += p[i] - p[i - 1] - 1;
		ret = max(ret, i - l + 1);
	}
//	printf("ret = %d\n", ret);
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	rep(i, 0, n) {
		int c;
		scanf("%d", &c);
		vec[c].pb(i);
	}
	int ans = 1;
	rep(i, 1, m + 1) 
		ans = max(ans, solve(vec[i]));
	printf("%d", ans);	
	return 0;
}