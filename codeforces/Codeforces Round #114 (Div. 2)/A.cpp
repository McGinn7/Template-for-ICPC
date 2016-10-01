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
ll n, x, y;
bool check(ll p) {
	return 1ll * 100 * (x + p) >= n * y;
}
int main() {
	cin >> n >> x >> y;
	int l = 0, r = INF;
	while (l + 1 < r) {
		int m = (l + r) >> 1;	
		check(m) ? r = m : l = m;
	}
	int ans = (check(l) ? l : r);
	cout << ans << endl;
	return 0;
}