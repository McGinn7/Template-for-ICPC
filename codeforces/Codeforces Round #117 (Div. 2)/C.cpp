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
int n, k, len, a[N];
bool vis[N];
ll solve() {
	memset(vis, false, sizeof(vis));
	ll sum = 0, ret = 0;
	int op = k;
	priority_queue<pii> que, rev;
	rep(i, 0, len) {
		sum += a[i];
		if (a[i] < 0)
			que.push(mp(-a[i], i));
	}
	while (op > 0 && !que.empty()) {
		--op;
		vis[que.top().second] = true;
		sum += que.top().first * 2ll;
		rev.push(mp(-que.top().first, que.top().second));
		que.pop();
	}
	ret = max(ret, sum);
	rep(i, len, n) {
		if (vis[i - len]) {
			++op, sum += a[i - len];
		} else {
			sum -= a[i - len];
		}
		sum += a[i];
		if (a[i] < 0)
			que.push(mp(-a[i], i));
		while (op > 0 && !que.empty()) {
			if (que.top().second <= i - len) {
				que.pop();
				continue;
			}
			--op;
			vis[que.top().second] = true;
			sum += que.top().first * 2ll;
			rev.push(mp(-que.top().first, que.top().second));
			que.pop();
		}
		while (!que.empty() && !rev.empty()) {
			if (que.top().second <= i - len) {
				que.pop();
				continue;
			}
			if (rev.top().second <= i - len) {
				rev.pop();
				continue;	
			}
			if (que.top().first > -rev.top().first) {
				pii q = que.top(), r = rev.top();
				que.pop(), rev.pop();
				vis[q.second] = true, vis[r.second] = false;
				sum -= 2ll * a[q.second], sum += 2ll * a[r.second]; 
				rev.push(mp(a[q.second], q.second));
				que.push(mp(-a[r.second], r.second));
			} else {
				break;
			}
		}
		ret = max(ret, sum);
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &len);
	rep(i, 0, n)
		scanf("%d", a + i);
	scanf("%d", &k);
	ll ans = solve();
	rep(i, 0, n) a[i] = -a[i];
	ans = max(ans, solve());
	cout << ans << endl;
	return 0;
}
