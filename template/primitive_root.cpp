vector<int> factor(int n) {
	vector<int> ret;
	rep(i, 2, sqrt(n) + 1) 
		if (n % i == 0) {
			ret.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		ret.push_back(n);
	return ret;
}
int getPrimitiveRoot(int n) {
	// here we assume n is a prime
	int phi = n - 1;	
	vector<int> p = factor(phi);
	for (int g = 1; ; ++g) {
		bool flag = true;
		rep(i, 0, sz(p))
			if (kpow(g, phi / p[i], n) == 1) {
				flag = false;
				break;
			}
		if (flag)
			return g;
	}
	return -1;
}
