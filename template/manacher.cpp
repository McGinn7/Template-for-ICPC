vector<int> manacher(const string &s) {
	// make sure s.length() > 0 
	// abcde → a#b#c#d#e
	// s[i/2-L[i]+1, (i+1)/2+L[i]-1] is a palindrome
	vector<int> L(2 * s.length() - 1);
	L[0] = 1;
	for (int i = 1, j = 0; i < L.size(); ++i) {
		int p = i / 2;
		int q = p + (i & 1);	
		int r = (j + 1) / 2 + L[j] - 1; // rightmost
		L[i] = q > r ? 0 : min(r - q + 1, L[2 * j - i]);	
		while (p - L[i] >= 0 && q + L[i] < L.size()
			&& s[p - L[i]] == s[q + L[i]])
			++L[i];
		if (q + L[i] - 1 > r) j = i;
	}
	return L;
}
