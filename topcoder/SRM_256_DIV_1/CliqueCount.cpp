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

int s, a[20];
bool cli[1 << 20], cnt[1 << 20];

class CliqueCount {
public:
	int n;
	int countCliques(vector<string> graph) {
		n = sz(graph);
		rep(i, 0, 1 << n)
			cli[i] = cnt[i] = false;
		cli[0] = true;
		rep(i, 1, 1 << n)
			if (cli[i ^ (i & -i)]) {
				int j = 0;
				while (j < n && !(i >> j & 1))
					++j;
				cli[i] = cli[i ^ (i & -i)];
				rep(k, j + 1, n)
					if (i >> k & 1)
						cli[i] &= (graph[j][k] == '1');
				cnt[i] = cli[i];
			}
		for (int i = (1 << n) - 1; i > 0; --i)
			if (cli[i]) {
				rep(j, 0, n)
					if (i >> j & 1)
						cnt[i ^ (1 << j)] = false;
			}
		int ans = 0;
		rep(i, 0, 1 << n)
			if (cnt[i])
				++ans;
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
		string Arr0[] = { "010", "100", "000" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		verify_case(0, Arg1, countCliques(Arg0));
	}
	void test_case_1() {
		string Arr0[] = { "011", "101", "110" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 1;
		verify_case(1, Arg1, countCliques(Arg0));
	}
	void test_case_2() {
		string Arr0[] = { "00010000000000100000", "00110000000000000000",
				"01011001000000011000", "11101000000100010110",
				"00110000001100000000", "00000000010000000001",
				"00000000000000011001", "00100000000010000001",
				"00000000000100011000", "00000100000010000010",
				"00001000000000000010", "00011000100001000101",
				"00000001010000000000", "00000000000100000010",
				"10000000000000000010", "00110010100000000000",
				"00100010100000000000", "00010000000100000000",
				"00010000011001100000", "00000111000100000000" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 28;
		verify_case(2, Arg1, countCliques(Arg0));
	}
	void test_case_3() {
		string Arr0[] = { "00", "00" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		verify_case(3, Arg1, countCliques(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	CliqueCount ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
