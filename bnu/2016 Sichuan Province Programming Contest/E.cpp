#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e15 + 7;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
//----------head-----------
ll a[3];
ll solve() {
	rep(i, 0, 3)
		if (a[i] == a[0] + a[1] + a[2])
			return a[i];
	if (a[0] == 0) {
		if (a[1] == 1) {
			return 3 + (a[2] - 1) * 2;
		} else {
			return 2 * a[1] + 3 * a[2] - 2;
		}
	} else {
		if (a[1] == 0) {
			if (a[0] >= 2)
				return a[0] + 3 * a[2];
			else
				return 2 * a[2] + 1;
		} else {
			return a[0] + 2 * a[1] + 3 * a[2];
		}
	}
}
int main() {
	rep(i, 0, 3)
		cin >> a[i];
	cout << solve();
	return 0;
}