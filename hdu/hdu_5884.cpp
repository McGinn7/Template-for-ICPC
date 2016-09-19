#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
int n, T, a[N], b[N];
bool check(int k) {
	int i = 0, j = 0, m = 0, cnt = (n - 1) % (k - 1);
	ll sum = 0;
	if (cnt > 0) {
		int tmp = 0;
		while (i <= cnt)
			tmp += a[i++];
		sum += tmp, b[m++] = tmp;
	}
	while ((n - i) + (m - j) > 1) {
		int tmp = 0;
		rep(_k, 0, k) {
			if (i < n && (j >= m || a[i] <= b[j])) {
				tmp += a[i++];
			} else {
				tmp += b[j++];
			}
		}
		sum += tmp, b[m++] = tmp;
	}
	return sum <= T;
}
int solve() {
	int l = 2, r = n;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		check(mid) ? r = mid : l = mid;
	}
	return check(l) ? l : r;
}
int main() {
	int TT;
	scanf("%d", &TT);
	rep(cas, 0, TT) {
		scanf("%d%d", &n, &T);
		rep(i, 0, n)
			scanf("%d", &a[i]);
		sort(a, a + n);
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
