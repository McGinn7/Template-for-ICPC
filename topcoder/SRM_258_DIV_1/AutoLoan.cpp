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

const double EPS = 1e-16;

class AutoLoan {
public:
	double calc(double price, double pay, int term, double rate) {
		rep(i, 0, term)
			price = price * (1 + rate) - pay;
		return price;
	}
	double interestRate(double price, double monthlyPayment, int loanTerm) {
		double l = 0, r = 1;
		rep(time, 0, 1000)
		{
			double mid = (l + r) / 2.0;
			double ret = calc(price, monthlyPayment, loanTerm, mid);
			if (ret > EPS)
				r = mid;
			else
				l = mid;
		}
		return l * 12 * 100;
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
		double Arg0 = 6800;
		double Arg1 = 100;
		int Arg2 = 68;
		double Arg3 = 1.3322616182218813E-13;
		verify_case(0, Arg3, interestRate(Arg0, Arg1, Arg2));
	}
	void test_case_1() {
		double Arg0 = 2000;
		double Arg1 = 510;
		int Arg2 = 4;
		double Arg3 = 9.56205462458368;
		verify_case(1, Arg3, interestRate(Arg0, Arg1, Arg2));
	}
	void test_case_2() {
		double Arg0 = 15000;
		double Arg1 = 364;
		int Arg2 = 48;
		double Arg3 = 7.687856394581649;
		verify_case(2, Arg3, interestRate(Arg0, Arg1, Arg2));
	}
	void test_case_3() {
		double Arg0 = 1.0;
		double Arg1 = 0.142857142857143;
		int Arg2 = 7;
		double Arg3 = 3.9968010105369827E-13;
		verify_case(2, Arg3, interestRate(Arg0, Arg1, Arg2));
	}


// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	AutoLoan ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
