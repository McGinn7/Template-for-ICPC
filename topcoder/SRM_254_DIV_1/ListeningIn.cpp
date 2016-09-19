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

class ListeningIn {
public:
	string probableMatch(string typed, string phrase) {
		stringstream ss;
		int p = 0;
		for (int i = 0; i < sz(phrase); ++i)
			if (p < sz(typed) && phrase[i] == typed[p])
				++p;
			else
				ss << phrase[i];
		if (p == sz(typed)) {
			return ss.str();
		} else {
			return "UNMATCHED";
		}
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
		string Arg0 = "cptr";
		string Arg1 = "capture";
		string Arg2 = "aue";
		verify_case(0, Arg2, probableMatch(Arg0, Arg1));
	}
	void test_case_1() {
		string Arg0 = "port to me";
		string Arg1 = "teleport to me";
		string Arg2 = "tele";
		verify_case(1, Arg2, probableMatch(Arg0, Arg1));
	}
	void test_case_2() {
		string Arg0 = "back  to base";
		string Arg1 = "back to base";
		string Arg2 = "UNMATCHED";
		verify_case(2, Arg2, probableMatch(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	ListeningIn ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
