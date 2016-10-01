#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<sstream>
#include<iomanip>
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
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
int n, a, b, d[N];
pii seg[N][2];
queue<int> que;
int dis(int i, int j) {
	int dx = 0, dy = 0;
	if (seg[i][1].first < seg[j][0].first) {
		dx = seg[j][0].first - seg[i][1].first;
	} else if (seg[j][1].first < seg[i][0].first) {
		dx = seg[i][0].first - seg[j][1].first;
	}
	if (seg[i][1].second < seg[j][0].second) {
		dy = seg[j][0].second - seg[i][1].second;
	} else if (seg[j][1].second < seg[i][0].second) {
		dy = seg[i][0].second - seg[j][1].second;
	}
	return dx * dx + dy * dy;
}
int main() {
	scanf("%d%d", &a, &b);
	rep(i, 0, 2) {
		int x, y;
		scanf("%d%d", &x, &y);
		seg[i][0] = seg[i][1] = mp(x, y);
	}
	scanf("%d", &n);
	n += 2;
	rep(i, 2, n) {
		rep(j, 0, 2) {
			int x, y;
			scanf("%d%d", &x, &y);
			seg[i][j] = mp(x, y);
		}
		if (seg[i][0].first == seg[i][1].first) {
			if (seg[i][0].second > seg[i][1].second)
				swap(seg[i][0].second, seg[i][1].second);
		} else {
			if (seg[i][0].first > seg[i][1].first)
				swap(seg[i][0].first, seg[i][1].first);
		}
	}
	fill_n(d, n, INF);
	d[0] = 0, que.push(0);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		rep(i, 0, n)
			if (d[i] > d[u] + 1 && dis(u, i) <= a * a) {
				d[i] = d[u] + 1;
				que.push(i);
			}
	}
	if (d[1] == INF) {
		printf("-1");
	} else {
		double ans = INF;
		rep(i, 0, n)
			if (d[i] + 1 == d[1]) {
				ans = min(ans, (a + b) * d[i] + sqrt(dis(i, 1)));
			}
		printf("%.8lf\n", ans);
	}
	return 0;
}