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

const int N = 107;
const double EPS = 1e-9;

struct Point {
	double x, y;
	Point() {

	}
	Point(double _x, double _y) {
		x = _x, y = _y;
	}
	Point operator+(const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	double operator^(const Point &p) const {
		return x * p.y - y * p.x;
	}
} tmp[N], p[2][N];
int n[2];

int sign(double x) {
	if (fabs(x) < EPS)
		return 0;
	return x > 0 ? 1 : -1;
}

class ConvexPolygons {
public:
	Point seg_inter_pnt(Point &a, Point &b, Point &c, Point &d) {
		double s1 = (b - a) ^ (c - a), s2 = (b - a) ^ (d - a);
		Point ret;
		ret.x = (c.x * s2 - d.x * s1) / (s2 - s1);
		ret.y = (c.y * s2 - d.y * s1) / (s2 - s1);
		return ret;
	}
	double area_poly(Point p[], int n) {
		double ret = 0;
		p[n] = p[0];
		rep(i, 0, n)
			ret += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
		return fabs(ret) / 2.0;
	}
	double convex_poly_inter_area(Point p1[], Point p2[], int n1, int n2) {
		int tn, i = 0, j, nxt, now;
		p1[n1] = p1[0], p2[n2] = p2[0];
		for (i = 0; i < n1 && n2 > 2; ++i) {
			now = sign((p1[i + 1] - p1[i]) ^ (p2[0] - p1[i + 1]));
			for (j = tn = 0; j < n2; ++j, now = nxt) {
				if (now >= 0)
					tmp[tn++] = p2[j];
				nxt = sign((p1[i + 1] - p1[i]) ^ (p2[j + 1] - p1[i + 1]));
				if (now * nxt < 0)
					tmp[tn++] = seg_inter_pnt(p1[i], p1[i + 1], p2[j],
							p2[j + 1]);
			}
			for (j = 0; j < tn; ++j)
				p2[j] = tmp[j];
			n2 = tn, p2[tn] = p2[0];
		}
		if (n2 < 3)
			return 0.0;
		return area_poly(p2, n2);
	}
	void input(vector<string> vec, Point p[], int &n) {
		n = sz(vec);
		stringstream ss;
		rep(i, 0, n)
		{
			double x, y;
			ss.clear();
			ss << vec[i];
			ss >> x >> y;
			p[i] = Point(x, y);
		}
	}
	double overlap(vector<string> polygon1, vector<string> polygon2) {
		input(polygon1, p[0], n[0]);
		input(polygon2, p[1], n[1]);
		return convex_poly_inter_area(p[0], p[1], n[0], n[1]);
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
	void verify_case(int Case, const double &Expected, const double &Received) {
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
		string Arr0[] = { "00 00", "02 00", "00 03" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "1 1", "3 1", "3 3", "1 3" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		double Arg2 = 0.08333333333333326;
		verify_case(0, Arg2, overlap(Arg0, Arg1));
	}
	void test_case_1() {
		string Arr0[] = { "-1 -1", "1 -1", "1 1", "-1 1" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "-2 -2", "0 -2", "2 -2", "2 0", "2 2", "0 2", "-2 2",
				"-2 0" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		double Arg2 = 4.0;
		verify_case(1, Arg2, overlap(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "-1 -1", "-2 -1", "-1 -2" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "1 1", "2 1", "1 2" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		double Arg2 = 0.0;
		verify_case(2, Arg2, overlap(Arg0, Arg1));
	}
	void test_case_3() {
		string Arr0[] = { "-2 0", "-1 -2", "1 -2", "2 0", "1 2", "-1 2" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "0 -3", "1 -1", "2 2", "-1 0" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		double Arg2 = 5.233333333333333;
		verify_case(3, Arg2, overlap(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	ConvexPolygons ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
