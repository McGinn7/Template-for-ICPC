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
const double EPS = 1e-10;
class Pitches {
public:
	double calc(double p[], double x) {
		double ret = 1e9;
		rep(y, 0, 2)
			ret = min(ret,
					p[0] * x * y + p[1] * x * (1.0 - y) + p[2] * (1.0 - x) * y
							+ p[3] * (1.0 - x) * (1.0 - y));
		return ret;
	}
	double strikeOut(vector<double> stats, int balls, int strikes) {
		if (balls == 4)
			return 0.0;
		if (strikes == 3)
			return 1.0;
		double p[4];
		p[0] = stats[0] * strikeOut(stats, balls + 1, strikes)
				+ stats[1] * strikeOut(stats, balls, strikes + 1);
		p[1] = stats[2] * strikeOut(stats, balls + 1, strikes)
				+ stats[3] * strikeOut(stats, balls, strikes + 1);
		p[2] = stats[4] * strikeOut(stats, balls + 1, strikes)
				+ stats[5] * strikeOut(stats, balls, strikes + 1);
		p[3] = stats[6] * strikeOut(stats, balls + 1, strikes)
				+ stats[7] * strikeOut(stats, balls, strikes + 1);
		double l = 0.0, r = 1.0;
		while (l + EPS < r) {
			double x = l + (r - l) / 3.0, y = r - (r - l) / 3;
			if (calc(p, x) < calc(p, y))
				l = x;
			else
				r = y;
		}
		return calc(p, l);
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
	void verify_case(int Case, const double &Expected, const double &Received) {
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
		double Arr0[] = { 0, 0, 0, 1, 0, 1, 0, 0 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		int Arg2 = 2;
		double Arg3 = 0.5;
		verify_case(0, Arg3, strikeOut(Arg0, Arg1, Arg2));
	}
	void test_case_1() {
		double Arr0[] = { 0.375, 0.25, 0.375, 0.25, 0.375, 0.25, 0.375, 0.25 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 0;
		int Arg2 = 2;
		double Arg3 = 0.39208984375;
		verify_case(1, Arg3, strikeOut(Arg0, Arg1, Arg2));
	}
	void test_case_2() {
		double Arr0[] = { 0.33, 0, 0, 1, 0.44, 0, 0, 1 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		int Arg2 = 1;
		double Arg3 = 0.0;
		verify_case(2, Arg3, strikeOut(Arg0, Arg1, Arg2));
	}
	void test_case_3() {
		double Arr0[] = { 0, 1, 0, 1, 0, 0, 0, 0 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		int Arg2 = 1;
		double Arg3 = 1.0;
		verify_case(3, Arg3, strikeOut(Arg0, Arg1, Arg2));
	}
	void test_case_4() {
		double Arr0[] = { 0, 0.4, 0.05, 0.75, 0.2, 0.7, 0.85, 0.1 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 0;
		int Arg2 = 0;
		double Arg3 = 0.32194802205218886;
		verify_case(4, Arg3, strikeOut(Arg0, Arg1, Arg2));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	Pitches ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
