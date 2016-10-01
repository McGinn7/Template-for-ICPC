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
bool dfs(ll a, ll b) { // a <= b
	if (a == 0 || b == 0)
		return false;
	if (!dfs(b % a, a))
		return true;
	ll k = b / a;
	return k % (a + 1) % 2 == 0;
}
int main() {
	int T;
	cin >> T;
	rep(cas, 0, T) {
		ll a, b;
		cin >> a >> b;
		if (a > b)
			swap(a, b);
		if (dfs(a, b))
			cout << "First" << endl;
		else
			cout << "Second" << endl;
	}
	return 0;
}