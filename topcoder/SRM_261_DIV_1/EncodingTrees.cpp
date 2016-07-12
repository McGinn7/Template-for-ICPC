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

ll h[] = { 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012,
		742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190 };

class EncodingTrees {
public:
	string _str(char ch) {
		stringstream ss;
		ss << ch;
		return ss.str();
	}
	string dfs(int N, int index, char b) {
		if (index > h[N])
			return "";
		int sum = 0;
		rep(i, 0, N)
			if (sum + h[i] * h[N - i - 1] >= index) {
				if (i == 0)
					return _str(b + i) + dfs(N - 1, index - sum, b + i + 1);
				if (i == N - 1)
					return _str(b + i) + dfs(N - 1, index - sum, b);
				int l = 1, r = h[i];
				while (l + 1 < r) {
					int m = (l + r) >> 1;
					sum + m * h[N - i - 1] >= index ? r = m : l = m;
				}
				int p = (sum + l * h[N - i - 1] >= index ? l : r);
				return _str(b + i) + dfs(i, p, b)
						+ dfs(N - i - 1, index - sum - (p - 1) * h[N - i - 1],
								b + i + 1);
				break;
			} else {
				sum += h[i] * h[N - i - 1];
			}
		return "";
	}
	string getCode(int N, int index) {
		return dfs(N, index, 'a');
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
	void verify_case(int Case, const string &Expected, const string &Received) {
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
		int Arg0 = 2;
		int Arg1 = 1;
		string Arg2 = "ab";
		verify_case(0, Arg2, getCode(Arg0, Arg1));
	}
	void test_case_1() {
		int Arg0 = 2;
		int Arg1 = 2;
		string Arg2 = "ba";
		verify_case(1, Arg2, getCode(Arg0, Arg1));
	}
	void test_case_2() {
		int Arg0 = 2;
		int Arg1 = 3;
		string Arg2 = "";
		verify_case(2, Arg2, getCode(Arg0, Arg1));
	}
	void test_case_3() {
		int Arg0 = 4;
		int Arg1 = 9;
		string Arg2 = "cbad";
		verify_case(3, Arg2, getCode(Arg0, Arg1));
	}
	void test_case_4() {
		int Arg0 = 15;
		int Arg1 = 14023;
		string Arg2 = "abcdeohgfniljkm";
		verify_case(4, Arg2, getCode(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	EncodingTrees ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
