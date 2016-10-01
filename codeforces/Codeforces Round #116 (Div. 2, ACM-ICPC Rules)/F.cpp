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
int n, a[N], p[N];
int main() {
	scanf("%d", &n);
	rep(i, 1, n + 1)
		scanf("%d", a + i);
	rep(i, 1, n + 1) {
		int bi;
		scanf("%d", &bi);
		p[a[i]] = bi;
	}
	rep(i, 1, n + 1) {
		if (i - 1)
			putchar(' ');
		printf("%d", p[i]);
	}
	return 0;
}