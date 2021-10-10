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
 
const int N = 1e5 + 7;
 
int n, y[N];
 
vector<int> solve() {
  vector<int> st;
  int min_y = INT_MAX;
  int max_y = INT_MIN;
  rep(i, 1, n + 1) {
    int ny = y[i];
    if (ny < min_y) {
      if (!st.empty() && st.back() == min_y)
        st.pop_back();
      min_y = ny;
      st.emplace_back(ny);
    } else if (ny > max_y) {
      if (!st.empty() && st.back() == max_y)
        st.pop_back();
      max_y = ny;
      st.emplace_back(ny);
    }
  }
  return st;
}
 
void output(const vector<int> &st) {
  for (auto x : st) cout << x << ", ";
  cout << endl;
}
 
int main() {
  scanf("%d", &n);
  rep(i, 1, n + 1) scanf("%d", y + i);
 
  vector<int> left = solve();
 
  reverse(y + 1, y + n + 1);
  vector<int> right = solve();
 
  puts(left == right ? "YES" : "NO");
 
  return 0;  
}