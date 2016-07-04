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

int c[30];
pair<int, int> p[30];

class Decipher {
public:
	string solve(string str) {
		rep(i, 0, sz(str))
			if ('A' <= str[i] && str[i] <= 'Z') {
				str[i] = 'A' + c[str[i] - 'A'];
			}
		return str;
	}
	vector<string> decipher(vector<string> encoded, string frequencyOrder) {
		rep(i, 0, 26)
			p[i] = mp(0, i);
		rep(i, 0, sz(encoded))
			rep(j, 0, sz(encoded[i]))
				if ('A' <= encoded[i][j] && encoded[i][j] <= 'Z')
					--p[encoded[i][j] - 'A'].first;
		sort(p, p + 26);
		rep(i, 0, sz(frequencyOrder))
			c[p[i].second] = frequencyOrder[i] - 'A';
		vector<string> ans;
		rep(i, 0, sz(encoded))
			ans.pb(solve(encoded[i]));
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
	void verify_case(int Case, const vector<string> &Expected,
			const vector<string> &Received) {
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
		string Arr0[] = { "ABBBCC" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "XYZ";
		string Arr2[] = { "ZXXXYY" };
		vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		verify_case(0, Arg2, decipher(Arg0, Arg1));
	}
	void test_case_1() {
		string Arr0[] = { "RZLW" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "CEFD";
		string Arr2[] = { "EDCF" };
		vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		verify_case(1, Arg2, decipher(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "XX YYY Z YYY XX", "WWWWWZWWWWW" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "ETMQ";
		string Arr2[] = { "MM TTT Q TTT MM", "EEEEEQEEEEE" };
		vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		verify_case(2, Arg2, decipher(Arg0, Arg1));
	}
	void test_case_3() {
		string Arr0[] = { " X ", "", " ", "  ", "   " };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "B";
		string Arr2[] = { " B ", "", " ", "  ", "   " };
		vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		verify_case(3, Arg2, decipher(Arg0, Arg1));
	}
	void test_case_4() {
		string Arr0[] = { "RAZVLHAR KNW CNR", "HEA HNFMNSAR NFAK" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "EORTPNFHSCDIWG";
		string Arr2[] = { "REGISTER NOW FOR", "THE TOPCODER OPEN" };
		vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
		verify_case(4, Arg2, decipher(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	Decipher ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
