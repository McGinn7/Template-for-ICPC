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
const int N = 4e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n;
char s[N];
vector<int> p, ans;
bool solve() {
	if (!sz(p))
		return false;
	if (p.front() == 0 || p.front() > 8)
		return false;
	if (p.back() == n - 1 || n - p.back() > 4)
		return false;
	rep(i, 1, sz(p)) {
		int d = p[i] - p[i - 1] - 1;
		if (!(2 <= d && d <= 11))
			return false;
	}
	rep(i, 1, sz(p)) {
		int d = p[i] - p[i - 1] - 1;
		rep(j, 1, 4)
			if (1 <= d - j && d - j <= 8) {
				ans.pb(p[i - 1] + j);
				break;
			}
	}
	ans.pb(n - 1);
	return true;
}
int main() {
	scanf("%s", s);
	n = strlen(s);
	rep(i, 0, n)
		if (s[i] == '.')
			p.pb(i);
	if (solve()) {
		puts("YES");
		int last = 0;
		rep(i, 0, sz(ans)) {
			rep(j, last, ans[i] + 1)
				putchar(s[j]);
			last = ans[i] + 1, puts("");
		}
	} else {
		puts("NO");
	}
	return 0;
}