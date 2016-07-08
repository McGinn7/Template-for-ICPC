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

class CompressionText {
public:
	int n, f[55];
	int solve(string s, string a, string b) {
		f[0] = 0, f[1] = 1, f[2] = 2;
		rep(i, 3, n + 1)
		{
			f[i] = f[i - 1] + 1;
			if (s.substr(i - 3, 3) == a || s.substr(i - 3, 3) == b)
				f[i] = min(f[i], f[i - 3] + 2);
		}
		return f[n];
	}
	int shortestLength(string original) {
		n = sz(original);
		int ret = n;
		rep(i, 0, n)
			rep(j, i, n)
				if (i + 2 < n && j + 2 < n)
					ret = min(ret,
							solve(original, original.substr(i, 3),
									original.substr(j, 3)));
		return ret;
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
		string Arg0 = "BARXFOO";
		int Arg1 = 5;
		verify_case(0, Arg1, shortestLength(Arg0));
	}
	void test_case_1() {
		string Arg0 = "FOOFOO BAR";
		int Arg1 = 7;
		verify_case(1, Arg1, shortestLength(Arg0));
	}
	void test_case_2() {
		string Arg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYABCDEFGHIJKLMNOPQRSTUVWXY";
		int Arg1 = 46;
		verify_case(2, Arg1, shortestLength(Arg0));
	}
	void test_case_3() {
		string Arg0 = "QWERTYUIOPASDFGHJKLZXCVBNM";
		int Arg1 = 24;
		verify_case(3, Arg1, shortestLength(Arg0));
	}
	void test_case_4() {
		string Arg0 = "BBAAAABBBBAAABABABBBABABAAABABABAAABBAABABBBABAAAB";
		int Arg1 = 40;
		verify_case(4, Arg1, shortestLength(Arg0));
	}
	void test_case_5() {
		string Arg0 = "AAA";
		int Arg1 = 2;
		verify_case(5, Arg1, shortestLength(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	CompressionText ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
