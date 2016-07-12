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

int cnt[1000];

class PrimeStatistics {
public:
	int mostCommonRemainder(int lowerBound, int upperBound, int modulo) {
		vector<bool> p(upperBound + 1);
		rep(i, 0, sz(p))
			p[i] = ((i & 1) == 1);
		p[1] = false, p[2] = true;
		for (int i = 3; i * i < sz(p); i += 2)
			if (p[i])
				for (int j = i * i; j < sz(p); j += i << 1)
					p[j] = false;
		rep(i, 0, modulo)
			cnt[i] = 0;
		rep(i, lowerBound, upperBound + 1)
			if (p[i])
				++cnt[i % modulo];
		int ans = 0;
		rep(i, 0, modulo)
			if (cnt[i] > cnt[ans])
				ans = i;
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
		if ((Case == -1) || (Case == 3))
			test_case_3();
		if ((Case == -1) || (Case == 4))
			test_case_4();
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
		int Arg0 = 3;
		int Arg1 = 14;
		int Arg2 = 5;
		int Arg3 = 3;
		verify_case(0, Arg3, mostCommonRemainder(Arg0, Arg1, Arg2));
	}
	void test_case_1() {
		int Arg0 = 3;
		int Arg1 = 33;
		int Arg2 = 1000;
		int Arg3 = 3;
		verify_case(1, Arg3, mostCommonRemainder(Arg0, Arg1, Arg2));
	}
	void test_case_2() {
		int Arg0 = 25;
		int Arg1 = 27;
		int Arg2 = 17;
		int Arg3 = 0;
		verify_case(2, Arg3, mostCommonRemainder(Arg0, Arg1, Arg2));
	}
	void test_case_3() {
		int Arg0 = 1;
		int Arg1 = 200000;
		int Arg2 = 2;
		int Arg3 = 1;
		verify_case(3, Arg3, mostCommonRemainder(Arg0, Arg1, Arg2));
	}
	void test_case_4() {
		int Arg0 = 1;
		int Arg1 = 1000;
		int Arg2 = 6;
		int Arg3 = 5;
		verify_case(4, Arg3, mostCommonRemainder(Arg0, Arg1, Arg2));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	PrimeStatistics ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
