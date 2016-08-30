#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<vector>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
typedef long long ll;
typedef unsigned long long ul;
typedef pair<int, int> pii;
const ul BASE = 107;
const ll LINF = 1e10 + 7;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 268435456;
const double PI = acos(-1.0);
const double EPS = 1e-8;
//-----------------head-----------------
int n, X, L, a[N], f[N], sum[N];
int rt, tot, dp[N * 30], par[N * 30], ch[N * 30][2];
void _max(int &x, int y) {
	if (x < y)
		x = y;
}
void input() {
	int P, Q;
	scanf("%d%d%d", &n, &X, &L);
	scanf("%d%d%d", &a[1], &P, &Q);
	sum[1] = a[1];
	rep(i, 2, n + 1)
	{
		a[i] = (1ll * a[i - 1] * P + Q) % MOD;
		sum[i] = sum[i - 1] ^ a[i];
	}
}
int newnode() {
	++tot;
	dp[tot] = par[tot] = 0, ch[tot][0] = ch[tot][1] = 0;
	return tot;
}
void ins(int val, int _dp) {
	int p = rt;
	for (int i = 29; i >= 0; --i) {
		int x = val >> i & 1;
		if (!ch[p][x]) {
			ch[p][x] = newnode();
			par[ch[p][x]] = p;
		}
		p = ch[p][x];
	}
	while (p != rt) {
		_max(dp[p], _dp);
		p = par[p];
	}
}
void del(int val, int _dp) {
	int p = rt;
	for (int i = 29; i >= 0; --i) {
		int x = val >> i & 1;
		if (!ch[p][x])
			return;
		p = ch[p][x];
	}
	if (dp[p] == _dp) {
		dp[p] = -1;
		while (p != rt) {
			dp[p] = 0;
			rep(i, 0, 2)
				if (ch[p][i])
					_max(dp[p], dp[ch[p][i]]);
			p = par[p];
		}
	}
}
int qry(int val) {
	int p = rt, ret = -1;
	for (int i = 29; i >= 0; --i)
		if (X >> i & 1) {
			if (ch[p][val >> i & 1])
				_max(ret, dp[ch[p][val >> i & 1]]);
			if (!ch[p][(val >> i & 1) ^ 1])
				return ret;
			p = ch[p][(val >> i & 1) ^ 1];
		} else {
			if (!ch[p][val >> i & 1])
				return ret;
			p = ch[p][val >> i & 1];
		}
	_max(ret, dp[p]);
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		input();
		tot = 0;
		rt = newnode();
		ins(0, 0);
		rep(i, 1, n + 1)
		{
			if (i - L - 1 >= 1)
				del(sum[i - L - 1], f[i - L - 1]);
			f[i] = qry(sum[i]) + 1;
			if (f[i])
				ins(sum[i], f[i]);
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
/*
 3
 3 1 2
 1 1 1
 3 0 3
 1 1 1
 3 1 1
 3 0 3
 */