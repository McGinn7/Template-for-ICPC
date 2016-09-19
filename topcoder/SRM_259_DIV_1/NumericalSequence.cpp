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

class NumericalSequence {
public:
	int makePalindrome(vector<int> s) {
		int ret = 0, l = 0, r = sz(s) - 1;
		while (l < r) {
			if (s[l] == s[r]) {
				++l, --r;
				continue;
			}
			if (l + 1 == r) {
				++ret;
				break;
			}
			++ret;
			if (s[l] < s[r]) {
				s[l + 1] += s[l];
				++l;
			} else {
				s[r - 1] += s[r];
				--r;
			}
		}
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
		int Arr0[] = { 15, 78, 78, 15 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 0;
		verify_case(0, Arg1, makePalindrome(Arg0));
	}
	void test_case_1() {
		int Arr0[] = { 1, 1, 1, 3 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		verify_case(1, Arg1, makePalindrome(Arg0));
	}
	void test_case_2() {
		int Arr0[] = { 15, 78, 87, 51 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		verify_case(2, Arg1, makePalindrome(Arg0));
	}
	void test_case_3() {
		int Arr0[] =
				{ 3, 23, 21, 23, 42, 39, 63, 76, 13, 13, 13, 32, 12, 42, 26 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 8;
		verify_case(3, Arg1, makePalindrome(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	NumericalSequence ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
