#include <cmath>
#include <cstring>
#include <iomanip>
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

const int INF = 1e9;

int n, cnt[11], sum[11], bid[55][11], ask[55][11];

class StockQuotes {
public:
	void MIN(int &x, int y) {
		if (x > y)
			x = y;
	}
	void MAX(int &x, int y) {
		if (x < y)
			x = y;
	}
	vector<string> report(vector<string> quotes) {
		n = sz(quotes);
		memset(cnt, 0, sizeof(cnt));
		memset(sum, 0, sizeof(sum));
		memset(bid, -1, sizeof(bid));
		memset(ask, -1, sizeof(ask));
		rep(i, 1, n + 1)
		{
			stringstream ss;
			ss << quotes[i - 1];
			int id, b, a;
			ss >> id >> b >> a;
			rep(j, 0, 10)
				bid[i][j] = bid[i - 1][j], ask[i][j] = ask[i - 1][j];
			bid[i][id] = b, ask[i][id] = a;
			bid[i][10] = -INF, ask[i][10] = INF;
			rep(j, 0, 10)
			{
				if (~bid[i][j])
					MAX(bid[i][10], bid[i][j]);
				if (~ask[i][j])
					MIN(ask[i][10], ask[i][j]);
			}
			rep(j, 0, 11)
			{
				if (bid[i][j] == -1 || ask[i][j] == -1)
					continue;
				if (bid[i][j] == bid[i - 1][j] && ask[i][j] == ask[i - 1][j])
					continue;
				++cnt[j], sum[j] += ask[i][j] - bid[i][j];
			}
		}
		vector<string> res;
		rep(i, 0, 11)
			if (cnt[i] > 0) {
				stringstream ss;
				ss << setprecision(2) << fixed << i << " " << cnt[i] << " "
						<< floor(100.0 * sum[i] / cnt[i] + 0.5) / 100.0;
				res.push_back(ss.str());
			}
		return res;
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
		string Arr0[] = { "0 10 14", "1 9 16", "2 11 15", "0 11 13", "1 10 15",
				"2 12 14", "0 9 15", "2 8 20" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "0 3 4.00", "1 2 6.00", "2 3 6.00", "10 6 2.83" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		verify_case(0, Arg1, report(Arg0));
	}
	void test_case_1() {
		string Arr0[] = { "8 931 944", "8 926 946", "8 926 951", "8 928 953",
				"8 929 954" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "8 5 21.60", "10 5 21.60" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		verify_case(1, Arg1, report(Arg0));
	}
	void test_case_2() {
		string Arr0[] = { "2 711 730", "5 716 729", "7 711 734", "0 718 731",
				"5 713 731", "1 713 730" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "0 1 13.00", "1 1 17.00", "2 1 19.00", "5 2 15.50",
				"7 1 23.00", "10 4 13.75" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		verify_case(2, Arg1, report(Arg0));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	StockQuotes ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
