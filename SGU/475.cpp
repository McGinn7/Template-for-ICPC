#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout<<#x<<" = "<<x<<", "
#define de(x) cout<<#x<<" = "<<x<<endl
//-------
const int N = 10;
const int M = 1e3 + 7;
const int INF = INT_MAX / 2;

int n, w[N], t[N], s[N], T[1 << N], W[1 << N];
int m, c[M], d[M], D[M];
int dp[1 << N], dps[1 << N];

inline void _min(int &x, int y) {
	x = min(x, y);
}

int main() {
	scanf("%d%d", &n, &m);	
	rep(i, 0, n) scanf("%d%d%d", w + i, t + i, s + i);
	rep(i, 0, m) scanf("%d%d%d", c + i, D + i, d + i);

	const int MSK = (1 << n) - 1;
	rep(msk, 1, 1 << n) rep(i, 0, n)
		if (msk >> i & 1) {
			T[msk] = max(T[msk ^ 1 << i], t[i]);
			W[msk] = W[msk ^ 1 << i] + w[i];
			break;
		}	

	rep(msk, 1, 1 << n) dp[msk] = INF;

	rep(j, 0, m) {
		rep(msk, 0, 1 << n) {
			dps[msk] = dp[msk];
			dp[msk] = INF;
		}
		rep(i, 0, n) rep(msk, 0, 1 << n) {
			_min(dps[msk ^ 1 << i], dps[msk] + s[i]);
		}
		rep(msk, 0, 1 << n) {
			int dj = W[msk] <= c[j] ? d[j] : D[j];
			_min(dp[msk], dps[msk] + max(dj, T[MSK ^ msk]));
		}
		dp[0] = INF; // not empty
	}
	int ans = INT_MAX;
	rep(msk, 0, 1 << n) {
		int tmp = dp[msk];
		rep(i, 0, n) if (msk >> i & 1) tmp += s[i];
		_min(ans, tmp);
	}
	printf("%d\n", ans);


	return 0;
}

