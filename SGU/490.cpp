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

const int N = 22;
char g[N][N];


void solve() {
	int h, w, n; scanf("%d%d%d", &h, &w, &n);
	rep(i, 0, h) rep(j, 0, w) g[i][j] = '.';

	rep(i, 1, h - 1) {
		for (int j = 1 + (~i & 1); j < w - 1; j += 2) {
			g[i][j] = n-- > 0 ? '#' : '.';
		}
	}

	if (n > 0) {
		puts("Impossible");
		return ;
	}

	rep(i, 0, h) {
		g[i][w] = 0;	
		puts(g[i]);
	}
}

int main() {
	int T; scanf("%d", &T);
	rep(cas, 0, T) {
		if (cas > 0) puts("");
		solve();
	}
	return 0;
}

