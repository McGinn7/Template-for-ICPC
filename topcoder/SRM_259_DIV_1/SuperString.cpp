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

class SuperString {
public:
	int n, sum[3000][30];
	char str[3000];
	int cmp(int i, int j, int l, int r) {
		int len = min(j - i + 1, r - l + 1);
		rep(p, 0, len)
			if (str[i + p] != str[l + p])
				return str[i + p] < str[l + p] ? -1 : 1;
		return r - l > j - i ? -1 : 1;
	}
	string goodnessSubstring(vector<string> superstring) {
		n = 0;
		rep(i, 0, sz(superstring))
			rep(j, 0, sz(superstring[i]))
				str[++n] = superstring[i][j];
		rep(i, 0, 26)
			sum[0][i] = 0;
		rep(i, 1, n + 1)
		{
			rep(j, 0, 26)
				sum[i][j] = sum[i - 1][j];
			++sum[i][str[i] - 'A'];
		}
		int l = 1, r = 1, ans = 1;
		rep(i, 1, n + 1)
			rep(j, i, n + 1)
			{
				if (j - i + 1 < ans)
					continue;
				int cnt = 0;
				rep(k, 0, 26)
					if (sum[j][k] - sum[i - 1][k] == 1) {
						++cnt;
					}
				if (cnt > ans || (cnt == ans && cmp(i, j, l, r) == -1)) {
					ans = cnt;
					l = i, r = j;
				}
			}
		stringstream ss;
		rep(i, l, r + 1)
			ss << str[i];
		return ss.str();
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
		string Arr0[] = { "CHALLENGE" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "CHALLENG";
		verify_case(0, Arg1, goodnessSubstring(Arg0));
	}
	void test_case_1() {
		string Arr0[] = { "THEWORD" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "THEWORD";
		verify_case(1, Arg1, goodnessSubstring(Arg0));
	}
	void test_case_2() {
		string Arr0[] = { "THE", "MULTI", "LINE", "TEST" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "HEMULTI";
		verify_case(2, Arg1, goodnessSubstring(Arg0));
	}
	void test_case_3() {
		string Arr0[] = { "ZYXWVUTSRQPONMLKJIHGFEDCBA",
				"ZYXWVUTSRQPONMLKJIHGFEDCBA" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arg1 = "AZYXWVUTSRQPONMLKJIHGFEDCB";
		verify_case(3, Arg1, goodnessSubstring(Arg0));
	}

// END CUT HERE

}
;
// BEGIN CUT HERE
int main() {
	SuperString ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
