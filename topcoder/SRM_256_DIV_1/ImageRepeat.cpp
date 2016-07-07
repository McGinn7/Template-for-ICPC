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
typedef unsigned long long UL;

const int N = 3e3 + 7;
const UL BASE = 137;
UL ha[55][55], hb[55][55], base[N];

class ImageRepeat {
public:
	int na, ma, nb, mb;
	UL hsv(UL f[], int l, int r) {
		return l ? f[r] - f[l - 1] * base[r - l + 1] : f[r];
	}
	bool check(int k) {
		set<UL> S;
		rep(j, 0, ma - k + 1)
		{
			UL hs = 0;
			rep(i, 0, k)
				hs = hs * base[k] + hsv(ha[i], j, j + k - 1);
			S.insert(hs);
			rep(i, k, na)
			{
				hs = hs - hsv(ha[i - k], j, j + k - 1) * base[k * (k - 1)];
				hs = hs * base[k] + hsv(ha[i], j, j + k - 1);
				S.insert(hs);
			}
		}
		rep(j, 0, mb - k + 1)
		{
			UL hs = 0;
			rep(i, 0, k)
				hs = hs * base[k] + hsv(hb[i], j, j + k - 1);
			if (S.find(hs) != S.end())
				return true;
			rep(i, k, nb)
			{
				hs = hs - hsv(hb[i - k], j, j + k - 1) * base[k * (k - 1)];
				hs = hs * base[k] + hsv(hb[i], j, j + k - 1);
				if (S.find(hs) != S.end())
					return true;
			}
		}
		return false;
	}
	void calc(vector<string> &img, UL hs[][55], int n, int m) {
		rep(i, 0, n)
		{
			hs[i][0] = img[i][0];
			rep(j, 1, m)
				hs[i][j] = hs[i][j - 1] * BASE + img[i][j];
		}
	}
	int largestSize(vector<string> imageA, vector<string> imageB) {
		base[0] = 1;
		rep(i, 1, N)
			base[i] = base[i - 1] * BASE;
		na = sz(imageA), ma = sz(imageA[0]);
		nb = sz(imageB), mb = sz(imageB[0]);
		calc(imageA, ha, na, ma), calc(imageB, hb, nb, mb);
		int l = 0, r = min(min(na, ma), min(nb, mb));
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			check(mid) ? l = mid : r = mid;
		}
		return check(r) ? r : l;
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
		string Arr0[] = { "ABC", "BCD", "CDE" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "ABC", "BCD", "CDE" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 3;
		verify_case(0, Arg2, largestSize(Arg0, Arg1));
	}
	void test_case_1() {
		string Arr0[] = { "ABC", "BCD", "CDE" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "ABCXX", "BCDXX", "CDFXX" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 2;
		verify_case(1, Arg2, largestSize(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "CEBACBABBDCCCACCDCBD", "EBAEBCBEBBCCEABEECED",
				"CEAEAEEEADBDEDABDCCB", "EDCEACDABDBCBEECACBD",
				"CDCBCBCCBCCCADDCAEDC", "ACCBAABABDABEDEACABC",
				"DCCADCACAEBCBCCCEEEB", "ACDABCCCBAABBAEBCBDA",
				"BACEEADBBDBAABCCBDBE", "AACACCCEEEBEBDCEABAD",
				"CABACEAAEDDEDDAAEDCC", "DDCEAEEBBDBEDBACCCAE",
				"CDABEEEDBDEBCEBECEAB", "CDBBDDCDCEDBDEEBCEDD",
				"DBDDBCBAEBBCDAECEBDA", "DBBBECAECACADAACACEA",
				"BDADACDEECCBABADEDDC", "AEBCABCCABCBBCBABBEC",
				"DDCEAEDEDBCBBABBCCBC", "DBBEEAEDDCABCEAACBEC" };
		vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
		string Arr1[] = { "CBEEADAEDCDDCEBEEADC", "BDBDABCBBDBACEACDACA",
				"ABAABDAADBCECDCEAACE", "DDBAAAACAAAAECBDAEDA",
				"EEAAABABCDABAEBEABAE", "CECADCCEABEBEDCAEABA",
				"DDECACDEECBBCBDDCDAE", "CAEAAEDBADEECAACDAAA",
				"EAECECBCDAAEBDECBBAB", "CBCDADDDBACEDBBABACC",
				"DCAEAADBEBEACDEDCCEC", "ACACCBEACEBBBBEEACEC",
				"DEDEBEEADCAECEBDDBEA", "ACACACEADCACEAACEDAD",
				"DCACBEEBCBDEDADACEEC", "EDDEDCDCCEDBCCDCABDC",
				"CABECBAEDCACABDDDADD", "CAEDAABCCCCDEDAEABDE",
				"CCDACADABADECDEACCED", "BEDADAADACAABAAEBADB" };
		vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
		int Arg2 = 3;
		verify_case(2, Arg2, largestSize(Arg0, Arg1));
	}

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	ImageRepeat ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
