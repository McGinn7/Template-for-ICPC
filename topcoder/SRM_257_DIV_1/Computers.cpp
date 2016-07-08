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

const int N = 1e3 + 7;
ll f[N][N];

class Computers {
public:
	long long choices(int n, int minDif, int minInComp, int amount) {
		f[0][0] = 1;
		rep(i, 1, amount)
		{
			rep(j, 0, n + 1)
				f[i][j] = f[i - 1][j];
			for (int k = minDif; k * i <= n; ++k)
				for (int j = k * i; j <= n; ++j)
					f[i][j] += f[i - 1][j - k * i];
		}
		ll ans = 0;
		for (int i = minInComp; i * amount <= n; ++i)
			ans += f[amount - 1][n - i * amount];
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
	void verify_case(int Case, const long long &Expected,
			const long long &Received) {
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
		int Arg0 = 20;
		int Arg1 = 6;
		int Arg2 = 5;
		int Arg3 = 2;
		long long Arg4 = 4LL;
		verify_case(0, Arg4, choices(Arg0, Arg1, Arg2, Arg3));
	}
	void test_case_1() {
		int Arg0 = 100;
		int Arg1 = 500;
		int Arg2 = 400;
		int Arg3 = 1;
		long long Arg4 = 0LL;
		verify_case(1, Arg4, choices(Arg0, Arg1, Arg2, Arg3));
	}
	void test_case_2() {
		int Arg0 = 1000;
		int Arg1 = 5;
		int Arg2 = 5;
		int Arg3 = 10;
		long long Arg4 = 113420686168080LL;
		verify_case(2, Arg4, choices(Arg0, Arg1, Arg2, Arg3));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	Computers ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
