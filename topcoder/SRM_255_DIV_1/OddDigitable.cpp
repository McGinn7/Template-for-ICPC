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

const int N = 1e5 + 7;
int que[N], pre[N], vis[N];

class OddDigitable {
public:
	string findMultiple(int N, int M) {
		memset(vis, -1, sizeof(vis));
		int qh = 0, qt = 0;
		que[qt++] = 0;
		while (qh < qt) {
			int v = que[qh++];
			for (int i = 1; i < 10; i += 2) {
				int nv = (v * 10 + i) % N;
				if (vis[nv] == -1) {
					vis[nv] = qt, que[qt] = nv, ++qt;
					pre[qt - 1] = (qh - 1) << 4 | i;
				}
			}
		}
		if (vis[M] == -1)
			return "-1";
		stringstream ss;
		int p = vis[M];
		while (p > 0) {
			ss << (pre[p] & 15);
			p = pre[p] >> 4;
		}
		string ret = ss.str();
		rep(i, 0, sz(ret) >> 1)
			swap(ret[i], ret[sz(ret) - i - 1]);
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
		int Arg0 = 10;
		int Arg1 = 7;
		string Arg2 = "7";
		verify_case(0, Arg2, findMultiple(Arg0, Arg1));
	}
	void test_case_1() {
		int Arg0 = 22;
		int Arg1 = 12;
		string Arg2 = "-1";
		verify_case(1, Arg2, findMultiple(Arg0, Arg1));
	}
	void test_case_2() {
		int Arg0 = 29;
		int Arg1 = 0;
		string Arg2 = "319";
		verify_case(2, Arg2, findMultiple(Arg0, Arg1));
	}
	void test_case_3() {
		int Arg0 = 5934;
		int Arg1 = 2735;
		string Arg2 = "791957";
		verify_case(3, Arg2, findMultiple(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	OddDigitable ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
