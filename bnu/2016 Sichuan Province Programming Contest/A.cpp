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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
//----------head-----------
struct Node {
	int x, y, z;
	void in() {
		scanf("%d%d%d", &x, &y, &z);
	}
} nd[3];
int main() {
	rep(i, 0, 3)
		nd[i].in();
	int dx = 0, dy = 0, dz = 0;
	if (nd[0].x < nd[1].x)
		dx = nd[1].x - nd[0].x;
	else if (nd[2].x < nd[0].x)
		dx = nd[0].x - nd[2].x;
	if (nd[0].y < nd[1].y)
		dy = nd[1].y - nd[0].y;
	else if (nd[2].y < nd[0].y)
		dy = nd[0].y - nd[2].y;
	if (nd[0].z < nd[1].z)
		dz = nd[1].z - nd[0].z;
	else if (nd[2].z < nd[0].z)
		dz = nd[0].z - nd[2].z;
	printf("%d\n", dx * dx + dy * dy + dz * dz);
	return 0;
}