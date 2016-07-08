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

class CardRemover {
public:
	int n, dp[55], c[55][55];
	bool f[55][55];
	int calc(string &a, string &b) {
		int ret = 0;
		rep(i, 0, sz(a))
			rep(j, 0, sz(b))
				ret += (a[i] == b[j]);
		return ret;
	}
	int calculate(vector<string> cards) {
		n = sz(cards);
		rep(i, 0, n)
			rep(j, 0, n)
				if (i != j)
					c[i][j] = calc(cards[i], cards[j]);
		memset(f, false, sizeof(f));
		rep(i, 0, n)
			f[i][i] = true;
		rep(i, 0, n - 1)
			f[i][i + 1] = true;
		rep(l, 3, n + 1)
			rep(i, 0, n + 1 - l)
				rep(k, i + 1, i + l - 1)
					if (f[i][k] && f[k][i + l - 1] && c[i][i + l - 1] >= 2)
						f[i][i + l - 1] = true;
		memset(dp, 0, sizeof(dp));
		rep(i, 0, n)
			rep(j, 0, i)
				if (f[j][i])
					dp[i] = max(dp[i], dp[j] + i - j - 1);
		return dp[n - 1];
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
		string Arr0[] = { "ABC", "CDE", "ABC", "CDE", "ABC" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		verify_case(0, Arg1, calculate(Arg0));
	}
	void test_case_1() {
		string Arr0[] = { "ABC", "CDE", "EFG", "GHI", "IJK" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 0;
		verify_case(1, Arg1, calculate(Arg0));
	}
	void test_case_2() {
		string Arr0[] = { "ADR", "FDB", "ABC", "CDE", "ABD" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		verify_case(2, Arg1, calculate(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	CardRemover ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
