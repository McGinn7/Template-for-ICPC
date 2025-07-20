# 普通平衡树

## 题目描述

您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：

1. 插入 x 数；
2. 删除 x 数（若有多个相同的数，只删除一个）；
3. 查询 x 数的排名（若有多个相同的数，输出最小的排名）；
4. 查询排名为 x 的数；
5. 求 x 的前驱（前驱定义为小于 x，且最大的数）；
6. 求 x 的后继（后继定义为大于 x，且最小的数）。

## 输入格式

第一行为 $n(1\le n\le 10^5)$，表示操作的个数，下面 $n$ 行每行有两个数 $\mathrm{opt}(1\le \mathrm{opt}\le 6)$ 和 $x(-10^7\le x\le 10^7)$，$\mathrm{opt}$ 表示操作的序号。

## 输出格式

对于操作 3、4、5、6 每行输出一个数，表示对应答案。

## 样例

### 输入

```textile
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598
```

### 输出

```textile
106465
84185
492737
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
//    if (x && rev[x]) rev[x] = 0, upd(ch[x][0]), upd(ch[x][1]);
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
int merge(int x, int y) {
    if (!x || !y) return x | y;
    loc(y, 1);
    link(y, 0, x);
    return y;
}
void remove(int &z, int v) {
    find_insert(z, v, 0);
    if (!z || val[z] != v) return ;
    --cc[z], --sz[z];
    if (cc[z] <= 0) {
        int l = ch[z][0], r = ch[z][1];
        fa[l] = fa[r] = 0;
        z = merge(l, r);
    }
}

int get_rank(int &z, int v) {
    find_insert(z, v, 0);
    return sz[ch[z][0]] + (val[z] < v ? cc[z] : 0) + 1;
}

int get_kth(int &z, int k) {
    loc(z, k);
    return val[z];
}

int get_prev(int &z, int v) {
    find_insert(z, v, 0);
    if (val[z] < v) return val[z];
    if (!ch[z][0]) return INT_MIN;
    loc(z, sz[ch[z][0]]);
    return val[z];
}

int get_next(int &z, int v) {
    find_insert(z, v, 0);
    if (val[z] > v) return val[z];
    if (!ch[z][1]) return INT_MAX;
    loc(z, sz[ch[z][0]] + cc[z] + 1);
    return val[z];
}

int main() {
    int rt = new_node(INT_MAX);
    int n; scanf("%d", &n);
    rep(_, 0, n) {
        int op, x; scanf("%d%d", &op, &x);
        switch(op) {
            case 1: find_insert(rt, x, 1); break;
            case 2: remove(rt, x); break;
            case 3: printf("%d\n", get_rank(rt, x)); break;
            case 4: printf("%d\n", get_kth(rt, x)); break;
            case 5: printf("%d\n", get_prev(rt, x)); break;
            case 6: printf("%d\n", get_next(rt, x)); break;
        }
    }

    return 0;
}
```
