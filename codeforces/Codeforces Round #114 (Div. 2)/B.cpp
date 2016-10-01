
 #include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<sstream>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e6 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const double Pi = acos(-1.0);
const double EPS = 1e-8;
//--------head--------
char str[N];
bool check(char str[]) {
	int i = 0;
	while (str[i] == ' ')
		++i;
	return str[i] == '#';
}
int main() {
	stringstream ss;
	bool last = true;
	while (gets(str) != NULL) {
		if (check(str)) {
			if (!last)
				puts("");
			puts(str), last = true;
		} else {
			for (int i = 0; str[i]; ++i)
				if (str[i] != ' ')
					putchar(str[i]);
			last = false;
		}
	}
	if (!last)
		puts("");
	return 0;
}