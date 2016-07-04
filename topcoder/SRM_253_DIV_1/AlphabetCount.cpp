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

ll f[55][55];
vector<int> p[26];

const int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

class AlphabetCount {
public:
	int n, m;
	int count(vector<string> grid, int length) {
		rep(i, 0, 26)
			p[i].clear();
		n = sz(grid), m = sz(grid[0]);
		rep(i, 0, n)
			rep(j, 0, m)
				f[i][j] = (grid[i][j] == 'A'), p[grid[i][j] - 'A'].pb(
						i << 6 | j);
		rep(i, 1, length)
			rep(j, 0, sz(p[i]))
			{
				int x, y;
				x = p[i][j] >> 6;
				y = p[i][j] ^ (x << 6);
				rep(k, 0, 8)
				{
					int xx, yy;
					xx = x + dx[k], yy = y + dy[k];
					if (!(0 <= xx && xx < n && 0 <= yy && yy < m))
						continue;
					if (grid[xx][yy] + 1 == grid[x][y])
						f[x][y] += f[xx][yy];
				}
			}
		ll ans = 0;
		rep(i, 0, sz(p[length - 1]))
		{
			int x, y;
			x = p[length - 1][i] >> 6;
			y = p[length - 1][i] ^ (x << 6);
			ans += f[x][y];
		}
		return min(ans, 1000000000ll);
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
		if ((Case == -1) || (Case == 6))
			test_case_6();
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
		string Arr0[] = { "ABC", "CBZ", "CZC", "BZZ", "ZAA" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		int Arg2 = 7;
		verify_case(0, Arg2, count(Arg0, Arg1));
	}
	void test_case_1() {
		string Arr0[] = { "AAAA", "AAAA", "AAAA" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 1;
		int Arg2 = 12;
		verify_case(1, Arg2, count(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "ABAB", "BABA", "ABAB", "BABA" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 2;
		int Arg2 = 24;
		verify_case(2, Arg2, count(Arg0, Arg1));
	}
	void test_case_3() {
		string Arr0[] = { "HIJKLMNOPQZZZONMLKHIDZYQR",
				"GYXWVUTSRASTZZPSTUJGECPXS", "FZABCDEFARQPUQRAAAVWFBOWT",
				"EONMJIHGAJMNOVAAAAAYXANUV", "DCBLKDEFIEKLEDWAAAZFGHMLK",
				"UVAZYBCGHFDFCAYXNPQZEDIJA", "TSWXAKLZGCZBGZIJOMZRUTCBZ",
				"RQPONMJIHBAZZHZZKLZZSVWXY" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 26;
		int Arg2 = 7;
		verify_case(3, Arg2, count(Arg0, Arg1));
	}
	void test_case_4() {
		string Arr0[] = { "CZC", "ZBZ", "AZA" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 3;
		int Arg2 = 4;
		verify_case(4, Arg2, count(Arg0, Arg1));
	}
	void test_case_5() {
		string Arr0[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 26;
		int Arg2 = 1000000000;
		verify_case(5, Arg2, count(Arg0, Arg1));
	}
	void test_case_6() {
		string Arr0[] = { "BDBCBACABDDCCADCBDDCBDDDBCCCCABACADDDCCCBADDDBADCA",
				"DCBBBACBDBACCADABCCAABACDBADBCBBABACBCADADCBDABBBD" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		int Arg1 = 4;
		int Arg2 = 20;
		verify_case(6, Arg2, count(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	AlphabetCount ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
