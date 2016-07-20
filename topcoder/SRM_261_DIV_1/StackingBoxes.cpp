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

const int N = 2e3 + 7;
const int INF = 1e9 + 7;

struct Node {
	int w, c;
	bool operator<(const Node &p) const {
		return w + c < p.w + p.c;
	}
} a[N];
stringstream ss;
int n, mw[N];

class StackingBoxes {
public:
	void _max(int &x, int y) {
		if (x < y)
			x = y;
	}
	int highestStack(vector<string> weight, vector<string> canCarry) {
		n = 0, ss.clear();
		rep(i, 0, sz(weight))
			ss << weight[i] << " ";
		while (ss >> a[n].w)
			++n;
		n = 0, ss.clear();
		rep(i, 0, sz(canCarry))
			ss << canCarry[i] << " ";
		while (ss >> a[n].c)
			++n;
		sort(a, a + n);
		rep(i, 0, n + 1)
			mw[i] = INF;
		mw[0] = 0;
		rep(i, 0, n)
			for (int j = i + 1; j > 0; --j)
				if (a[i].c >= mw[j - 1])
					mw[j] = min(mw[j], mw[j - 1] + a[i].w);
		int ans = 0;
		for (int i = n; i > 0; --i)
			if (mw[i] < INF) {
				ans = i;
				break;
			}
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
		string Arr0[] = { "10 20 30" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "11", "100 10" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 3;
		verify_case(0, Arg2, highestStack(Arg0, Arg1));
	}
	void test_case_1() {
		string Arr0[] = { "11 20 30" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "11", "100 10" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 2;
		verify_case(1, Arg2, highestStack(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "10", "20", "91" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "11", "100 10" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 2;
		verify_case(2, Arg2, highestStack(Arg0, Arg1));
	}
	void test_case_3() {
		string Arr0[] = { "100000" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "1000000000" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 1;
		verify_case(3, Arg2, highestStack(Arg0, Arg1));
	}
	void test_case_4() {
		string Arr0[] = { "100 100", "1000 100" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "90", "91 92 93" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 1;
		verify_case(4, Arg2, highestStack(Arg0, Arg1));
	}
	void test_case_5() {
		string Arr0[] = { "200 200 600 700 400" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "1000 20 150 700 10" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 3;
		verify_case(5, Arg2, highestStack(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	StackingBoxes ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
