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

int f[1 << 15];

class Piglets {
public:
	int n;
	int solve(int st) {
		if (!(st >> 0 & 1))
			return 0;
		if (!(st >> (n - 1) & 1))
			return n - 1;
		if (~f[st])
			return f[st];
		int p = -1, t = -1;
		rep(i, 1, n - 1)
			if (!(st >> i & 1)) {
				int nst = st | 1 << i, nt = 0;
				while (!((nst >> (i - 1) & 1) && (nst >> (i + 1) & 1)))
					++nt, nst |= 1 << solve(nst);
				if (nt > t)
					t = nt, p = i;
			}
		return f[st] = p;
	}
	int choose(string trough) {
		memset(f, -1, sizeof(f));
		n = sz(trough);
		int st = 0;
		rep(i, 0, n)
			if (trough[i] == 'p')
				st |= 1 << i;
		return solve(st);
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
		if ((Case == -1) || (Case == 3))
			test_case_3();
		if ((Case == -1) || (Case == 4))
			test_case_4();
		if ((Case == -1) || (Case == 5))
			test_case_5();
		if ((Case == -1) || (Case == 6))
			test_case_6();
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
		string Arg0 = "--p--";
		int Arg1 = 0;
		verify_case(0, Arg1, choose(Arg0));
	}
	void test_case_1() {
		string Arg0 = "p-p-p";
		int Arg1 = 1;
		verify_case(1, Arg1, choose(Arg0));
	}
	void test_case_2() {
		string Arg0 = "p--p";
		int Arg1 = 1;
		verify_case(2, Arg1, choose(Arg0));
	}
	void test_case_3() {
		string Arg0 = "p---p";
		int Arg1 = 2;
		verify_case(3, Arg1, choose(Arg0));
	}
	void test_case_4() {
		string Arg0 = "ppp";
		int Arg1 = -1;
		verify_case(4, Arg1, choose(Arg0));
	}
	void test_case_5() {
		string Arg0 = "p----p";
		int Arg1 = 3;
		verify_case(5, Arg1, choose(Arg0));
	}
	void test_case_6() {
		string Arg0 = "p-";
		int Arg1 = 1;
		verify_case(6, Arg1, choose(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	Piglets ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
