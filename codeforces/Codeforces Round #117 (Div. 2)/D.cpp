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
int p[N];
bool same[N];
char s[N], t[N];
vector<int> len(char s[], int p[]) {
	int n = strlen(s);
	p[0] = -1;
	for (int i = 1, j = -1; i < n; ++i) {
		while (j >= 0 && s[j + 1] != s[i])
			j = p[j];
		j += (s[j + 1] == s[i]);
		p[i] = j;
	}
	vector<int> ret;
	int x = n - 1;
	while (~x) {
		x = p[x];
		int y = n - 1 - x;
		if (n % y == 0)
			ret.pb(y);
	}
	return ret;
}
int solve() {
	int n = strlen(s), m = strlen(t);
	same[0] = s[0] == t[0];
	rep(i, 1, min(n, m)) 
		same[i] = same[i - 1] & (s[i] == t[i]);
//	rep(i, 0, min(n, m))
//		puts(same[i] ? "True" : "False");
	vector<int> ss = len(s, p), st = len(t, p);
//	rep(i, 0, sz(ss)) printf("%d ", ss[i]);puts("");
//	rep(i, 0, sz(st)) printf("%d ", st[i]);puts("");
	int i = 0, j = 0, ret = 0;
	while (i < sz(ss) && j < sz(st)) {
		if (ss[i] == st[j]) {
			if (same[ss[i] - 1])
				++ret;
			++i, ++j;
		} else {
			ss[i] < st[j] ? ++i : ++j;
		}
	}
	return ret;
}
int main() {
	scanf(" %s %s", s, t);
	cout << solve() << endl;
	return 0;
}