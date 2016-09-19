#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) (int(x.size()))
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;

vector<int> num;

class MagicCube {
public:
	int sum[3];
	void trans(int v, int a[]) {
		a[0] = v / 9, a[1] = (v - a[0] * 9) / 3, a[2] = v - a[0] * 9 - a[1] * 3;
	}
	int solve() {
		int mx = 0, mi = 1000000;
		int ii[3], jj[3];
		rep(i, 0, 27)
		{
			memset(sum, 0, sizeof(sum));
			trans(i, ii);
			rep(j, 0, 27)
			{
				trans(j, jj);
				rep(k, 0, 3)
					if (ii[k] != jj[k] && ii[(k + 1) % 3] == jj[(k + 1) % 3]
							&& ii[(k + 2) % 3] == jj[(k + 2) % 3]) {
						sum[k] += num[j];
					}
			}
			rep(j, 0, 3)
				mx = max(mx, sum[j] + num[i]), mi = min(mi, sum[j] + num[i]);
		}
		return mx - mi;
	}
	int getScore(vector<int> nums) {
		num = nums;
		int ans = solve();
		rep(i, 0, 27)
			rep(j, i + 1, 27)
			{
				swap(num[i], num[j]);
				ans = min(ans, solve());
				swap(num[i], num[j]);

			}
		return ans;
	}

// BEGIN CUT HERE
public:
	void run_test(int Case) {
		if ((Case == -1) || (Case == 0))
			test_case_0();
		if ((Case == -1) || (Case == 1))
			test_case_1();
		if ((Case == -1) || (Case == 2))
			test_case_2();
	}
private:
	template<typename T> string print_array(const vector<T> &V) {
		ostringstream os;
		os << "{ ";
		for (typename vector<T>::const_iterator iter = V.begin();
				iter != V.end(); ++iter)
			os << '\"' << *iter << "\",";
		os << " }";
		return os.str();
	}
	void verify_case(int Case, const int &Expected, const int &Received) {
		cerr << "Test Case #" << Case << "...";
		if (Expected == Received)
			cerr << "PASSED" << endl;
		else {
			cerr << "FAILED" << endl;
			cerr << "\tExpected: \"" << Expected << '\"' << endl;
			cerr << "\tReceived: \"" << Received << '\"' << endl;
		}
	}
	void test_case_0() {
		int Arr0[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 0;
		verify_case(0, Arg1, getScore(Arg0));
	}
	void test_case_1() {
		int Arr0[] = { 23, 4, 10, 1, 27, 21, 25, 7, 17, 9, 15, 13, 20, 3, 11, 2,
				22, 18, 12, 24, 14, 26, 8, 6, 5, 19, 16 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 18;
		verify_case(1, Arg1, getScore(Arg0));
	}
	void test_case_2() {
		int Arr0[] = { 23, 2, 10, 1, 27, 21, 25, 7, 17, 9, 15, 13, 20, 3, 11, 4,
				22, 18, 12, 24, 14, 26, 8, 6, 5, 19, 16 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 17;
		verify_case(2, Arg1, getScore(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	MagicCube ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
