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
const ll LINF = 1e18 + 7;
const ul BASE = 33;
const int N = 1e5 + 7;
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
char str[N];
vi p;
int check(char str[]) {
	int len = strlen(str);
	if (len >= 4 && strcmp(str + len - 4, "lios") == 0)
		return -1;
	if (len >= 3 && strcmp(str + len - 3, "etr") == 0)
		return -2;
	if (len >= 6 && strcmp(str + len - 6, "initis") == 0)
		return -3;
	if (len >= 5 && strcmp(str + len - 5, "liala") == 0)
		return 1;
	if (len >= 4 && strcmp(str + len - 4, "etra") == 0)
		return 2;
	if (len >= 6 && strcmp(str + len - 6, "inites") == 0)
		return 3;
	return 0;
}
bool solve() {
	while (~scanf(" %s", str))
		p.pb(check(str));
	bool mas = false, fem = false;
	rep(i, 0, sz(p))
	{
		if (!p[i])
			return false;
		mas |= (p[i] < 0);
		fem |= (p[i] > 0);
	}
	if (mas && fem)
		return false;
	if (sz(p) == 1)
		return true;
	bool noun = false;
	rep(i, 0, sz(p))
		switch (abs(p[i])) {
		case 1:
			if (noun)
				return false;
			break;
		case 2:
			if (noun)
				return false;
			noun = true;
			break;
		case 3:
			if (!noun)
				return false;
			break;
		}
	return noun;
}
int main() {
	puts(solve() ? "YES" : "NO");
	return 0;
}