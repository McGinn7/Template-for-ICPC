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
char str[N];
int n, UP, up;
int main() {
	scanf("%s", str);
	n = strlen(str);
	UP = up = 0;
	rep(i, 0, n)
		UP += ('A' <= str[i] && str[i] <= 'Z');
	int ans = min(UP, n - UP);
	rep(i, 0, n) {
		up += ('A' <= str[i] && str[i] <= 'Z');
		int tmp = (i + 1 - up) + (UP - up);
		ans = min(ans, tmp);
	}
	printf("%d", ans);
	return 0;
}
