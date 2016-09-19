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

const double EPS = 1e-9;

int a[5], w[21], b[5];
double ans;
vector<double> data;

class Predicting {
public:
	void dfs(int t, int sum) {
		if (t >= 4) {
			if (0 <= sum && sum <= 20) {
				rep(i, 0, 21)
					if (w[i] + sum == 10) {
						a[t] = i;
						break;
					}
				double tmp = 0;
				rep(i, 5, sz(data))
				{
					double val = 0;
					rep(j, 0, 5)
						val += data[i - j - 1] * w[a[j]];
					tmp += fabs(data[i] - val / 10.0);
					if (tmp > EPS + ans)
						return;
				}
				ans = tmp;
			}
			return;
		}
		rep(i, 0, 21)
			a[t] = i, dfs(t + 1, sum + w[i]);
	}
	double avgError(vector<double> _data) {
		w[0] = -10;
		rep(i, 1, 21)
			w[i] = w[i - 1] + 1;
		data = _data;
		ans = 1e9;
		dfs(0, 0);
		return ans / (sz(data) - 5);
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
		double Arr0[] = { 10, 10, 10, 10, 10, 10 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		double Arg1 = 0.0;
		verify_case(0, Arg1, avgError(Arg0));
	}
	void test_case_1() {
		double Arr0[] = { 50, 10, 50, 10, 50, 10, 50, 10, 50, 10, 50, 10 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		double Arg1 = 0.0;
		verify_case(1, Arg1, avgError(Arg0));
	}
	void test_case_2() {
		double Arr0[] = { 50, 60, 50, 60, 50, 60, 60 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		double Arg1 = 5.0;
		verify_case(2, Arg1, avgError(Arg0));
	}
	void test_case_3() {
		double Arr0[] = { 82.9102, 70.6848, 21.503, 61.4588, 54.7789, 48.9889,
				57.6766, 91.1859, 26.3674, 55.4601, 53.9357, 87.2005, 78.4771,
				65.0102, 18.619, 90.296, 26.3894, 53.8588, 91.8369, 58.8028,
				74.0577, 28.2406, 65.609, 59.4867, 27.7544, 54.6992, 69.2428,
				22.6264, 87.0083, 58.5116, 60.286, 20.4318, 65.6475, 11.8348,
				36.3488, 92.8092, 60.7392, 98.124, 48.1292, 39.5459, 52.2657,
				34.3519, 38.9279, 93.0152, 11.3157 };
		vector<double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		double Arg1 = 22.0175905;
		verify_case(3, Arg1, avgError(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	Predicting ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
