#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
#define pb push_back
#define mp make_pair
#define sz(x) (int(x.size()))
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;

class SlowDigitalClock {
public:
	int a[4], b[4];
	int calc(string &str, int p) {
		stringstream ss;
		ss << str;
		int h, m;
		char ch;
		ss >> h >> ch >> m;
		return h * p + m;
	}
	void solve(int x, int a[]) {
		a[0] = x / 10, a[1] = x % 10;
	}
	string firstCorrectTime(string currentTime, string clockTime,
			int secsPerMinute) {
		int cyc = (60) * (24 * 60 * secsPerMinute) / __gcd(60, secsPerMinute);
		int cur = calc(currentTime, 60), clo = calc(clockTime, 60);
		for (int t1 = 0, t2 = 0; t1 < cyc || t2 < cyc;) {
			int t = min(t1, t2);
			int x = (cur + t / 60) % (24 * 60);
			int y = (clo + t / secsPerMinute) % (24 * 60);
			solve(x / 60, a), solve(x % 60, a + 2);
			solve(y / 60, b), solve(y % 60, b + 2);
			if (t1 == t)
				t1 += 60;
			if (t2 == t)
				t2 += secsPerMinute;
			bool flag = true;
			rep(j, 0, 4)
				if (b[j] == 3 || b[j] == 4 || b[j] == 7) {
					flag = false;
					continue;
				}
			if (flag) {
				swap(b[0], b[3]), swap(b[1], b[2]);
				rep(j, 0, 4)
					if (b[j] == 6 || b[j] == 9)
						b[j] = 15 - b[j];
				flag = true;
				rep(j, 0, 4)
					if (a[j] != b[j]) {
						flag = false;
						break;
					}
				if (flag) {
					stringstream ss;
					ss << a[0] << a[1] << ":" << a[2] << a[3];
					return ss.str();
				}
			}
		}
		return "";
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
		string Arg0 = "01:11";
		string Arg1 = "21:09";
		int Arg2 = 61;
		string Arg3 = "01:12";
		verify_case(0, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_1() {
		string Arg0 = "01:10";
		string Arg1 = "21:09";
		int Arg2 = 61;
		string Arg3 = "01:12";
		verify_case(1, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_2() {
		string Arg0 = "12:50";
		string Arg1 = "05:21";
		int Arg2 = 125;
		string Arg3 = "12:50";
		verify_case(2, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_3() {
		string Arg0 = "05:46";
		string Arg1 = "23:50";
		int Arg2 = 240;
		string Arg3 = "11:10";
		verify_case(3, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_4() {
		string Arg0 = "12:34";
		string Arg1 = "23:45";
		int Arg2 = 197;
		string Arg3 = "02:11";
		verify_case(4, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_5() {
		string Arg0 = "12:34";
		string Arg1 = "23:45";
		int Arg2 = 300;
		string Arg3 = "";
		verify_case(5, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}
	void test_case_6() {
		string Arg0 = "00:00";
		string Arg1 = "00:01";
		int Arg2 = 86;
		string Arg3 = "01:22";
		verify_case(6, Arg3, firstCorrectTime(Arg0, Arg1, Arg2));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	SlowDigitalClock ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
