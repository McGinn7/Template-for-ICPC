#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
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
const int N = 3e2 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int n, a[N][N];
int main() {
	scanf("%d", &n);
	rep(i, 0, n) 
		rep(j, 0, n)
			scanf("%d", &a[i][j]);
	int ans = n * (n - 1) / 2;
	rep(i, 0, n)
		rep(j, i + 1, n) {
			bool flag = false;
			rep(k, 0, n)
				if (k != i && k != j && a[i][k] + a[k][j] == a[i][j]) {
					flag = true;
					break;
				}	
			if (flag)
				--ans;
		}
		printf("%d\n", ans);
	return 0;
}
