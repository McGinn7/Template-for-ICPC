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
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, b, a[N];
void solve() {
	int sum = b;
	rep(i, 0, n)
		sum += a[i];
	double ave = 1.0 * sum / n;
	rep(i, 0, n)
		if (a[i] > ave) {
			puts("-1");
			return ;
		}	
	rep(i, 0, n)
		printf("%.8lf\n", ave - a[i]);
}
int main() {
	scanf("%d%d", &n, &b);
	rep(i, 0, n) 
		scanf("%d", a + i);
	solve();
	return 0;
}