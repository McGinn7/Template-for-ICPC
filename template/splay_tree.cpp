#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 1e5 + 7;
int n, m, q, a[N];
struct Node {
	int ch[2], p, v, sz, rev, add;
	bitset<256> bit;
} t[N];
int rt;
void inc(int x, int d) {
	if (x) {
		t[x].v = (t[x].v + d) & 255;
		t[x].add = (t[x].add + d) & 255;	
		t[x].bit = (t[x].bit << d) | (t[x].bit >> (256 - d));				
	}
}
void flip(int x) {
	swap(t[x].ch[0], t[x].ch[1]), t[x].rev ^= 1;
}
void up(int x) {
	t[x].sz = 1 + t[t[x].ch[0]].sz + t[t[x].ch[1]].sz;
	t[x].bit = t[t[x].ch[0]].bit | t[t[x].ch[1]].bit;
	t[x].bit[t[x].v] = 1;
}
void down(int x) {
	if (t[x].add) {
		inc(t[x].ch[0], t[x].add);
		inc(t[x].ch[1], t[x].add);
		t[x].add = 0;
	}
	if (t[x].rev) {
		flip(t[x].ch[0]), flip(t[x].ch[1]);
		t[x].rev = 0;
	}
}
int build(int l, int r, int p) {
	if (l > r) return 0;
	int x = (l + r) >> 1;
	t[x].v = a[x] & 255, t[x].p = p, t[x].rev = t[x].add = 0;
	t[x].ch[0] = build(l, x - 1, x);
	t[x].ch[1] = build(x + 1, r, x);
	up(x);
	return x;
}
void rot(int x) {
	int y = t[x].p;
	down(y);
	down(x);
	if (rt == y) rt = x;
	int f = t[y].ch[0] == x;
	t[y].ch[!f] = t[x].ch[f];
	if (t[x].ch[f]) t[t[x].ch[f]].p = y;
	t[x].p = t[y].p;
	if (t[y].p) t[t[y].p].ch[t[t[y].p].ch[1] == y] = x;
	t[x].ch[f] = y;
	t[y].p = x;
	up(y);
}
void splay(int x, int g = 0) {
	if (t[x].p == g) down(x);
	else {
		while (t[x].p != g) rot(x);
		up(x);
	}
}
void rto(int k, int g = 0) {
	int x = rt;
	while (true) {
		down(x);
		if (t[t[x].ch[0]].sz + 1 == k)
			break;
		if (k <= t[t[x].ch[0]].sz) {
			x = t[x].ch[0];
		} else {
			k -= t[t[x].ch[0]].sz + 1;
			x = t[x].ch[1];
		}
	}
	splay(x, g);
}
#define key t[t[rt].ch[1]].ch[0]
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d%d", &n, &m, &q);
		rep(i, 0, n) rep(j, 0, m) scanf("%d", &a[i * m + j + 2]);
		rt = build(1, n * m + 2, 0);
		rep(_q, 0, q) {
			int op, k, l, r, z, L, R;
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d", &l, &r);
				--l, --r;
				L = R = l * m + r + 1;
			} else {
				scanf("%d%d%d", &k, &l, &r);
				--k, --l, --r;
				if (op == 3) {
					scanf("%d", &z);
					z &= 255;
				}
				L = 1 + k * m + l;
				R = 1 + k * m + r;
			}
			rto(L);
			rto(R + 2, rt);
			if (op == 1) {
				printf("%d\n", t[key].v);
			} else if (op == 2) {
				printf("%d\n", (int) t[key].bit.count());
			} else if (op == 3) {
				inc(key, z);
			} else {
				flip(key);
			}
		}
	}
	return 0;
}
