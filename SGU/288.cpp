#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<int>> VII;
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
const int P = 1e9 + 7;
inline void inc(int &x, int y) { if ((x += y) >= P) x -= P;}
template<typename T>
vector<vector<T>> VV(int n, int m, T v) {
  return vector<vector<T>>(n, vector<T>(m, v));
}
//-------

const int N = 2007;
int n, a[N][N];

void upd(int i, int j, int v) {
  a[i][j] = a[j][i] = v;
}

int solve(int n) {
  const int T = n - 1;
  rep(i, 0, n - 1) {
    rep(j, 0, i) {
      int v = i + j;
      if (v > T) v -= T;
      upd(i, j, v);
    }
  }
  rep(j, 0, n - 1) {
    int v = T + 2 * j;
    while (v > T) v -= T;
    upd(n - 1, j, v);
  }
  return T;
}

int main() {

  int real_n; scanf("%d", &real_n);
  if (real_n <= 1) {
    puts("0");
    return 0;
  }

  int T = solve(real_n + (real_n & 1));

  printf("%d\n", T);
  rep(i, 0, real_n) {
    rep(j, 0, real_n) {
      if (j) printf(" ");
      printf("%d", a[i][j]);
    }
    puts("");
  }

  return 0;
}

