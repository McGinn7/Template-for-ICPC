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

const int N = 11;
char num[N];
int n, f[N][N][N][2][2];

class PluCodeGenerator {
public:
	int dfs(int pos, int last1, int last2, int isp, int zero) {
		if (pos >= n)
			return zero ^ 1;
		if (~f[pos][last1][last2][isp][zero])
			return f[pos][last1][last2][isp][zero];
		int ret = 0;
		rep(i, 0, 10)
		{
			if (i && pos > 1 && i == last1 && i == last2)
				continue;
			if (!i && pos > 1 && !zero && i == last1 && i == last2)
				continue;
			if (isp && i + '0' > num[pos])
				continue;
			if (isp && i + '0' == num[pos])
				ret += dfs(pos + 1, last2, i, 1, zero & (i == 0));
			else
				ret += dfs(pos + 1, last2, i, 0, zero & (i == 0));
		}
		return f[pos][last1][last2][isp][zero] = ret;
	}
	int countInvalidCodes(int N) {
		--N;
		sprintf(num, "%d", N);
		n = strlen(num);
		memset(f, -1, sizeof(f));
		return N - dfs(0, 0, 0, 1, 1);
//		printf("N = %d, n = %d\n", N, n);
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
		int Arg0 = 111;
		int Arg1 = 0;
		verify_case(0, Arg1, countInvalidCodes(Arg0));
	}
	void test_case_1() {
		int Arg0 = 556;
		int Arg1 = 5;
		verify_case(1, Arg1, countInvalidCodes(Arg0));
	}
	void test_case_2() {
		int Arg0 = 1113;
		int Arg1 = 13;
		verify_case(2, Arg1, countInvalidCodes(Arg0));
	}
	void test_case_3() {
		int Arg0 = 7346556;
		int Arg1 = 323647;
		verify_case(3, Arg1, countInvalidCodes(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	PluCodeGenerator ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
