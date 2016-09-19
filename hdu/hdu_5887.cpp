#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
//-------------head------------
struct Node {
	int w, v;
	void in() {
		scanf("%d%d", &w, &v);
	}
	bool operator<(const Node &p) const {
		return 1ll * v * p.w > 1ll * w * p.v;
	}
} a[N];
int n, lim;
ll ans, sum[N];
bool check(int t, double W, double V) {
	rep(i, t, n)
		if (W + a[i].w <= lim) {
			W += a[i].w, V += a[i].v;
		} else {
			V += 1.0 * (lim - W) * a[i].v / a[i].w;
			break; 
		}
	return V <= ans;
}
void dfs(int t, ll W, ll V) {
	ans = max(ans, V);
	if (t >= n || check(t, W, V))
		return ;
	if (W + a[t].w <= lim)
		dfs(t + 1, W + a[t].w, V + a[t].v);
	dfs(t + 1, W, V);
}
int main() {
	while (~scanf("%d%d", &n, &lim)) {
		rep(i, 0, n)
			a[i].in();
		sort(a, a + n);
		sum[0] = a[0].v;
		rep(i, 1, n)
			sum[i] = sum[i - 1] + a[i].v;
		ans = 0;
		dfs(0, 0, 0);
		printf("%I64d\n", ans);
	}
	return 0;
}
