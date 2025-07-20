# # 文艺平衡树

## 题目描述

您需要写一种数据结构（可参考题目标题），来维护一个序列，其中需要提供以下操作：

翻转一个区间，例如原有序序列是 `5 4 3 2 1`，翻转区间是 [2, 4] 的话，结果是 `5 2 3 4 1`。

## 输入格式

第一行为 $n, m(1\le n,m\le 10^5)$，$n$ 表示初始序列有 $n$ 个数，这个序列依次是 $\{ 1, 2, \ldots n - 1, n \}$，$m$ 表示翻转操作次数。
接下来 $m$ 行每行两个数 $[l, r]$，数据保证 $1 \leq l \leq r \leq n$。

## 输出格式

输出一行 $n$ 个数字，表示原始序列经过 $m$ 次变换后的结果。

## 样例

### 输入

```textile
5 3
1 3
1 3
1 4
```

### 输出

```textile
4 3 2 1 5
```

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r-1);i>=(l);--i)
#define dd(x) cerr<<#x<<"="<<x<<","
#define de(x) cerr<<#x<<"="<<x<<endl
//-------
const int N = 1e5 + 7;

int val[N];

int idx, fa[N], cc[N], sz[N], rev[N], ch[N][2];
int new_node(int v, int _fa=0) {
	int x = ++idx;
	fa[x] = _fa, cc[x] = sz[x] = 1, rev[x] = ch[x][0] = ch[x][1] = 0;

	val[x] = v;
	return x;
}
inline void up(int x) {
	sz[x] = cc[x] + sz[ch[x][0]] + sz[ch[x][1]];
}
inline void upd(int x) {
	if (x) rev[x] ^= 1, swap(ch[x][0], ch[x][1]);
}
inline void down(int x) {
	if (x && rev[x]) rev[x] = 0, upd(ch[x][0]), upd(ch[x][1]);
}
inline int dir(int x) {
	return x == ch[fa[x]][1];
}
inline void link(int f, int d, int s) {
	if (f) down(f), ch[f][d] = s, up(f);
	if (s) fa[s] = f;
}
void rotate(int x) {
	int y = fa[x], z = fa[fa[x]], dx = dir(x), dy = dir(y);
	link(y, dx, ch[x][!dx]);
	link(x, !dx, y);
	link(z, dy, x);
}
void splay(int &z, int x) {
	for (int f = fa[z]; fa[x] != f; rotate(x))
		if (fa[fa[x]] != f) rotate(dir(x) == dir(fa[x]) ? fa[x] : x);
	z = x;
}
void find_insert(int &z, int v, int d=1) {
	int x = z, y = fa[z];
	while (x && val[x] != v) {
		down(x);
		x = ch[y = x][v > val[x]];
	}
	if (x) {
		cc[x] += d, sz[x] += d;
	} else if (d > 0) {
		x = new_node(v, y);
		link(y, v > val[y], x);
	}
	splay(z, x ? x : y);
}
void loc(int &z, int k) {
	for (int x = z, l = ch[z][0]; k <= sz[x]; l = ch[x][0]) {
		down(x);
		if (k <= sz[l]) {
			x = l;
		} else if (k <= sz[l] + cc[x]) {
			splay(z, x);
			break;
		} else {
			k -= sz[l] + cc[x];
			x = ch[x][1];
		}
	}
}

void dfs(int x, int L, int R) {
	if (!x) return ;
	down(x);
	dfs(ch[x][0], L, R);
	if (L <= val[x] && val[x] <= R) printf("%d ", val[x]);
	dfs(ch[x][1], L, R);
}

int main() {
	int n, m; scanf("%d%d", &n, &m);
	int rt = new_node(0);
	rep(i, 1, n + 2) find_insert(rt, i, 1);
	rep(_, 0, m) {
		int l, r; scanf("%d%d", &l, &r);
		loc(rt, l);
		loc(ch[rt][1], r - l + 2);
		upd(ch[ch[rt][1]][0]);
	}
	dfs(rt, 1, n);

	return 0;
}
```


