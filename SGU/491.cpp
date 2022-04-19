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

const int N = 1e5 + 7;
int ts[N];
vector<int> fac[N];

int main() {
	int n; scanf("%d", &n);
	ll ans = 0;
	for (int B = 1; B <= n; ++B) {
		for (int By = B; By <= n; By += B)
			for (auto A : fac[n - By]) {
				if (ts[A] != B) {
					++ans, ts[A] = B;
				}
			}
		for (int x = B; x <= n; x += B)
			fac[x].emplace_back(B);
	}
	printf("%lld", ans);
	return 0;
}

