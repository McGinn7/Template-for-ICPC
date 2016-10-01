
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e3 + 7;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int c[26];
char s[N], t[N];
void count(int n, char s[], int c[]) {
	memset(c, 0, sizeof(c[0]) * 26);
	rep(i, 0, n)
		++c[s[i] - 'a'];
}
void solve() {
	int n = strlen(s), m = strlen(t), L = -1, last = -1;
	count(n, s, c);
	rep(i, 0, min(n, m))
	{
		rep(j, t[i] - 'a' + 1, 26)
			if (c[j] > 0) {
				L = i;
				break;
			}
		if (!c[t[i] - 'a'])
			break;
		--c[t[i] - 'a'], last = i;
	}
	if (n > m && last == m - 1)
		L = m;
//	printf("L = %d\n", L);
	if (L == -1) {
		puts("-1");
		return;
	}
	count(n, s, c);
	rep(i, 0, L)
		putchar(t[i]), --c[t[i] - 'a'];
	rep(j, 0, 26)
		if (c[j] > 0 && ('a' + j) > t[L]) {
			putchar('a' + j), --c[j];
			break;
		}
	rep(i, L + 1, n)
		rep(j, 0, 26)
			if (c[j] > 0) {
				putchar('a' + j), --c[j];
				break;
			}
}
int main() {
	scanf("%s %s", s, t);
	solve();
	return 0;
}