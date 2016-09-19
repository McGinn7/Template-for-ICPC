#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<assert.h>
#include<sstream>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const ll LINF = 1e18 + 7;
const int N = 1e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 21092013;
const double EPS = 1e-8;
//-------------head-------------
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
struct Gauss {
	const static int N = 57;
	int a[N][N];
	void solve(int n, int m) {
		int i = 0, c = 0;
		for (; i < n && c < m; ++i, ++c) {
			int r = i;
			while (r < n && !a[r][c])
				++r;
			if (r >= n) {
				--i;
				continue;
			}
			if (r != i)
				swap(a[r], a[i]);
			rep(j, 0, n)
				if (i != j && a[j][c])
					for (int k = m; k >= c; --k)
						a[j][k] ^= a[i][k];
		}
	}
} G;
int id(int x, int y) {
	return x * 6 + y;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T)
	{
		memset(G.a, 0, sizeof(G.a));
		int tot = 5 * 6;
		rep(i, 0, 5)
			rep(j, 0, 6)
			{
				int st;
				scanf("%d", &st);
				G.a[id(i, j)][id(i, j)] = 1;
				G.a[id(i, j)][tot] = st;
				rep(k, 0, 4)
				{
					int x = i + dx[k], y = j + dy[k];
					if (x < 0 || x >= 5 || y < 0 || y >= 6)
						continue;
					G.a[id(i, j)][id(x, y)] = 1;
				}
			}
		G.solve(tot, tot);
		printf("PUZZLE #%d\n", cas + 1);
		rep(i, 0, tot)
		{
			int x = G.a[i][tot];
			printf("%d", x);
			if ((i + 1) % 6 == 0)
				puts("");
			else
				putchar(' ');
		}
	}
	return 0;
}