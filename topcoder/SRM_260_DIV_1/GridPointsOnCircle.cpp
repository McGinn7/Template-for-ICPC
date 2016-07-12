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

class GridPointsOnCircle {
public:
	int countPoints(int rSquare) {
		int ans = 0;
		for (int x = 1, X = sqrt(rSquare); x <= X; ++x) {
			int y = sqrt(rSquare - x * x);
			if (y > 0 && x * x + y * y == rSquare)
				++ans;
		}
		int r = sqrt(rSquare);
		ans += (r * r == rSquare);
		return ans << 2;
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
		int Arg0 = 1;
		int Arg1 = 4;
		verify_case(0, Arg1, countPoints(Arg0));
	}
	void test_case_1() {
		int Arg0 = 25;
		int Arg1 = 12;
		verify_case(1, Arg1, countPoints(Arg0));
	}
	void test_case_2() {
		int Arg0 = 3;
		int Arg1 = 0;
		verify_case(2, Arg1, countPoints(Arg0));
	}
	void test_case_3() {
		int Arg0 = 44;
		int Arg1 = 0;
		verify_case(3, Arg1, countPoints(Arg0));
	}
	void test_case_4() {
		int Arg0 = 50;
		int Arg1 = 12;
		verify_case(4, Arg1, countPoints(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	GridPointsOnCircle ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
