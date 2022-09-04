#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout<<#x<<" = "<<x<<", "
#define de(x) cout<<#x<<" = "<<x<<endl
//-------
 
const int N = 2e5 + 1;
 
int n, d, x[N], w[N];
 
int main() {
	scanf("%d%d", &n, &d);
	rep(i, 0, n) scanf("%d%d", x + i, w + i);
 
	tuple<int, int, int> ans(0, -1, -1);
 
	for (int i = 0, j = 0, mj = -1; i < n; ++i) {
		while (j < n && x[i] - x[j] >= d) {
			if (mj == -1 || w[mj] < w[j])
				mj = j;
			++j;
		}
		if (mj != -1) {
			ans = max(ans, make_tuple(w[mj] + w[i], mj + 1, i + 1));
		}
	}
 
	printf("%d %d\n", get<1>(ans), get<2>(ans));
	return 0;
}
