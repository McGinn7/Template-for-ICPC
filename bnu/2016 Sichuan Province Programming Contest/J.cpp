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
const int N = 2e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
//----------head-----------
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
int n, q, head, a[N];
int t[N * N][4];
int gcell(int r, int c) {
	int pos = head;
	rep(i, 0, r)
		pos = t[pos][2];
	rep(i, 0, c)
		pos = t[pos][1];
	return pos;
}
int grow(int r) {
	int ret = head;
	rep(i, 0, r)
		ret = t[ret][2];
	return ret;
}
int gcol(int c) {
	int ret = head;
	rep(i, 0, c)
		ret = t[ret][1];
	return ret;
}
void upd(int p, int r, int m, int d) {
	rep(i, 0, n)
	{
		a[i] = t[p][r];
		p = t[p][m];
	}
	for (int i = 0, j = (n - d + n) % n; i < n; ++i, j = (j + 1) % n) {
		t[p][r] = a[j], t[a[j]][(r + 2) % 4] = p;
		p = t[p][m];
	}
}
int main() {
	scanf("%d%d", &n, &q);
	rep(i, 0, n)
		rep(j, 0, n)
			rep(k, 0, 4)
			{
				int ni = (i + dx[k] + n) % n, nj = (j + dy[k] + n) % n;
				t[i * n + j][k] = ni * n + nj;
//				printf("t[%d][%d] = %d\n", i * n + j, k, t[i * n + j][k]);
			}
	head = 0;
	rep(_q, 0, q)
	{
		int t, l, r, d;
		scanf("%d%d%d%d", &t, &l, &r, &d);
		if (t == 1) {
			int L = grow(l), R = grow(r);
			if (l == 0)
				head = gcell(l, d);
			upd(L, 0, 1, d);
			upd(R, 2, 1, d);
		} else {
			int L = gcol(l), R = gcol(r);
			if (l == 0)
				head = gcell(d, l);
			upd(L, 3, 2, d);
			upd(R, 1, 2, d);
		}
	}
	rep(i, 0, n)
	{
		int p = grow(i);
		rep(j, 0, n)
		{
			if (j)
				putchar(' ');
			printf("%d", p);
			p = t[p][1];
		}
		puts("");
	}
	return 0;
}