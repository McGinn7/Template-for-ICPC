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

const int N = 1e4 + 7;
double g[N][100], f[4][N];
int to[100];
int c[13] = { 0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };

class ChutesAndLadders {
public:
	vector<double> winningChance(vector<int> startLadder, vector<int> endLadder,
			vector<int> players) {
		rep(i, 0, 100)
			to[i] = i;
		rep(i, 0, sz(startLadder))
			to[startLadder[i]] = endLadder[i];
		rep(i, 0, sz(players))
		{
			rep(j, 0, N)
				rep(k, 0, 100)
					g[j][k] = 0;
			g[0][players[i]] = 1;
			rep(j, 0, N - 1)
				rep(k, 0, 100)
					rep(d, 2, 13)
						g[j + 1][to[min(99, k + d)]] += g[j][k] * c[d] / 36.0;
			rep(j, 0, N)
				f[i][j] = g[j][99];
		}
		vector<double> ret(sz(players));
		rep(i, 1, N)
			rep(j, 0, sz(players)) {
				double p = f[j][i] - f[j][i - 1];
				rep(k, 0, j)
					p *= 1.0 - f[k][i];
				rep(k, j + 1, sz(players))
					p *= 1.0 - f[k][i - 1];
				ret[j] += p;
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
	void verify_case(int Case, const vector<double> &Expected,
			const vector<double> &Received) {
		cerr << "Test Case #" << Case << "...";
		if (Expected == Received)
			cerr << "PASSED" << endl;
		else {
			cerr << "FAILED" << endl;
			cerr << "\tExpected: " << print_array(Expected) << endl;
			cerr << "\tReceived: " << print_array(Received) << endl;
		}
	}
	void test_case_0() {
		int Arr0[] = { };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arr1[] = { };
		vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arr2[] = { 0, 0 };
		vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		double Arr3[] = { 0.6063557826968836, 0.3936442173031164 };
		vector<double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
		verify_case(0, Arg3, winningChance(Arg0, Arg1, Arg2));
	}
	void test_case_1() {
		int Arr0[] = { 7, 23, 42, 58, 87 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arr1[] = { 35, 91, 11, 31, 22 };
		vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arr2[] = { 0, 0, 0, 0 };
		vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		double Arr3[] = { 0.2850398049975441, 0.2591808222220256,
				0.23726366951493458, 0.21851570326549555 };
		vector<double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
		verify_case(1, Arg3, winningChance(Arg0, Arg1, Arg2));
	}
	void test_case_2() {
		int Arr0[] = { };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arr1[] = { };
		vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arr2[] = { 0, 30 };
		vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		double Arr3[] = { 0.013280440302841312, 0.9867195596971587 };
		vector<double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
		verify_case(2, Arg3, winningChance(Arg0, Arg1, Arg2));
	}
	void test_case_3() {
		int Arr0[] = { 79, 70, 50, 27, 3, 8, 35, 20, 97, 94, 92, 86, 53, 63, 61,
				46, 48, 15 };
		vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arr1[] = { 98, 90, 66, 83, 13, 30, 43, 41, 77, 74, 72, 23, 52, 59,
				18, 25, 10, 5 };
		vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arr2[] = { 21, 32, 56, 41 };
		vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		double Arr3[] = { 0.17890364754713348, 0.13868643400691752,
				0.5037066355391879, 0.17870328290676118 };
		vector<double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
		verify_case(3, Arg3, winningChance(Arg0, Arg1, Arg2));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	ChutesAndLadders ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
