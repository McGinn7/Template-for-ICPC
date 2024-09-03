#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------head------
struct Mat {
	static const int N = 2;
	int mod, a[N][N];
	void inc(int &x, int y) {
		x += y;
		if (x >= mod)
			x -= mod;
	}
	void init(int x, int _mod) {
		mod = _mod, x = (x % mod + mod) % mod;
		rep(i, 0, N)
			rep(j, 0, N)
				a[i][j] = (i == j ? x : 0);
	}
	Mat operator*(const Mat &p) {
		Mat ret;
		ret.init(0, mod);
		rep(i, 0, N) rep(j, 0, N) rep(k, 0, N)
			inc(ret.a[i][j], 1ll * a[i][k] * p.a[k][j] % mod);
		return ret;
	}
	Mat operator^(ll b) {
		Mat ret, a = *this;
		ret.init(1, mod);
		while (b > 0) {
			if (b & 1)
				ret = ret * a;
			a = a * a, b >>= 1;
		}
		return ret;
	}
} A;
const int N = 2e5 + 7;
bool prime[N];
vector<int> p;
ll kpow(ll a, ll b, ll mod) {
	ll r = 1;
	a = (a % mod + mod) % mod;
	while (b > 0) {
		if (b & 1)
			r = r * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return r;
}
void init() {
	A.a[0][0] = 1, A.a[0][1] = 1;
	A.a[1][0] = 1, A.a[1][1] = 0;
	memset(prime, true, sizeof(prime));
	rep(i, 2, N)
		if (prime[i]) {
			p.push_back(i);
			for (ll j = 1ll * i * i; j < N; j += i)
				prime[j] = false;
		}
}
vector<pair<ll, int> > factor(ll n) {
	vector<pair<ll, int> > ret;
	for (int i = 0, I = sqrt(n); i < sz(p) && p[i] <= I; ++i) 
		if (n % p[i] == 0) {
			ret.push_back(make_pair(p[i], 0));
			while (n % p[i] == 0)
				++ret.back().second, n /= p[i];
		}
	if (n > 1)
		ret.push_back(make_pair(n, 1));
	return ret;
}
vector<ll> work(ll n) {
	vector<ll> ret;
	for (int i = 1, I = sqrt(n); i <= I; ++i)
		if (n % i == 0) {
			ret.push_back(i);
			if (i * i != n)
				ret.push_back(n / i);
		}
	return ret;
}
ll loop(ll n) {
	vector<pair<ll, int> > vec = factor(n);
	ll ans = 1;
	rep(i, 0, sz(vec)) {
		ll re = 1, pi = vec[i].first;
		if (pi == 2) {
			re = 3;
		} else if (pi == 3) {
			re = 8;
		} else if (pi == 5) {
			re = 20;
		} else {
			vector<ll> fac = kpow(5, (pi - 1) >> 1, pi) == 1 
				? work(pi - 1) : work((pi + 1) << 1);
			sort(fac.begin(), fac.end());
			rep(k, 0, sz(fac)) {
				A.mod = pi;
				Mat B = A ^ (fac[k] - 1);
				ll x, y;
				x = (B.a[0][0] + B.a[0][1]) % pi;
				y = (B.a[1][0] + B.a[1][1]) % pi;
				if (x == 1 && y == 0) {
					re = fac[k];
					break;
				}
			}
		}
		rep(k, 1, vec[i].second)
			re *= pi;
		ans = ans / __gcd(ans, re) * re;
	}
	return ans;
}
ll P[N];
int main() {
	init();
	int n;
	scanf("%d", &n);
	printf("%lld", loop(n)); // mod n
	return 0;
}
