#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------

const int N = 1e3 + 7;
const int C = 51;

int n, m, c[2 * N], t[N][N];
unordered_map<int, int> R;
vector<int> e[2 * N];

int id(int x) {
  if (R.count(x)) return R[x];
  int ret = R.size();
  return R[x] = ret;
}

bool dfs(int u) {
  ll mask = 0; 
  for (auto v: e[u]) if (-1 != c[v]) {
    mask |= 1ll << c[v];
  }
  rep(i, 0, C) if (~mask >> i & 1) {
      c[u] = i;
      break;
  }
  if (-1 == c[u]) return false;
  for (auto v : e[u]) if (-1 == c[v]) {
    if (!dfs(v)) return false;
  }
  return true;
}

void solve() {

    rep(i, 1, n) {
      rep(j, 0, m) if (t[0][j] != t[i][j]) {
        int u = id(t[0][j]);
        int v = id(t[i][j]);
        e[u].emplace_back(v);
        e[v].emplace_back(u);
        break;
      }
    }

    const int k = R.size();

    rep(i, 0, k) c[i] = -1;
    rep(i, 0, k) if (-1 == c[i]) {
      if(!dfs(i)) {
        puts("No");
        return ;
      }
    }

    puts("Yes");
    set<int> S;
    rep(i, 0, n) rep(j, 0, m) S.insert(t[i][j]);
    for (auto x: S) {
      int y = 0;
      if (R.count(x)) y = c[R[x]];
      printf("%d -> %d\n", x, y);
    }
}

int main() {
  
  scanf("%d%d", &n, &m);
  rep(i, 0, n) rep(j, 0, m) scanf("%d", &t[i][j]);
  solve();

  return 0;
}
