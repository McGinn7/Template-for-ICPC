#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e3 + 7;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-8;
//--------head--------
int ty2(int b, int d) {
	rep(i, 1, 33)
	{
		d /= __gcd(b, d);
		if (d == 1)
			return i;
	}
	return 0;
}
bool ty3(int b, int d) {
	return (b - 1) % d == 0;
}
bool ty11(int b, int d) {
	return (b + 1) % d == 0;
}
bool ty6(int b, int d) {
	for (int i = 2; i <= d; ++i)
		if (d % i == 0) {
			int D = 1;
			while (d % i == 0)
				d /= i, D *= i;
			if (!ty2(b, D) && !ty3(b, D) && !ty11(b, D))
				return false;
		}
	return true;
}
void solve(int b, int d) {
	if (ty2(b, d)) {
		printf("2-type\n%d", ty2(b, d));
		return;
	}
	if (ty3(b, d)) {
		puts("3-type");
		return;
	}
	if (ty11(b, d)) {
		puts("11-type");
		return;
	}
	if (ty6(b, d)) {
		puts("6-type");
		return;
	}
	puts("7-type");
}
int main() {
	int b, d;
	scanf("%d%d", &b, &d);
	solve(b, d);
	return 0;
}